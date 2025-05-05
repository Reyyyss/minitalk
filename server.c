/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcarrasq <hcarrasq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 18:15:40 by hcarrasq          #+#    #+#             */
/*   Updated: 2025/05/05 15:57:01 by hcarrasq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	send_ack(pid_t client_pid)
{
	if (kill(client_pid, SIGUSR1) == -1)
		ft_printf("Error sending acknowledgement\n");
}		

void message_receiver(int sig, int len)
{
	static int		chars;
	static int		bits;
	static char		*str;
	static char		c;

	if (bits < 1)
		str = ft_calloc(len + 1, sizeof(char));
	if (sig == SIGUSR1)
		c |= (1 << (7 - (bits % 8)));
	bits++;
	if (bits % 8 == 0)
	{
		if (chars < len)
			str[chars++] = c;
		else if (chars == len)
		{
			ft_printf("%s\n", str);
			free(str);
			str = NULL;
			chars = 0;
			bits = 0;
		}
		c = 0;
	}
}
void signal_handler(int sig, siginfo_t *info, void *ucontext)
{
	static int		bit_len;
	static int		bits;
	static pid_t	client_id;

	(void)ucontext;
	if (!client_id || client_id != info->si_pid)
	{
		client_id = info->si_pid;
		bits = 0;
		bit_len = 0;
	}
	if (bits < 32)
	{
		bit_len = bit_len << 1;
		if (sig == SIGUSR1)
		bit_len |= 1;
		bits++;
	}
	else
		message_receiver(sig, bit_len);
	send_ack(client_id);
}

int	main(void)
{
	struct sigaction	sa;

	ft_printf("Server ID:%d\n", getpid());

	sa.sa_sigaction = signal_handler;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);

	if (sigaction(SIGUSR1, &sa, NULL) == -1 ||
		sigaction(SIGUSR2, &sa, NULL) == -1)
	{
		ft_printf("Error setting up signal handles\n");
		return (1);
	}
	while (1)
		pause();
	return (0);
}

