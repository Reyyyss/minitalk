/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcarrasq <hcarrasq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 18:15:40 by hcarrasq          #+#    #+#             */
/*   Updated: 2025/04/25 15:56:36 by hcarrasq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void message_receiver(int sig, int len)
{
	int	chars;
	static int		bits;
	static char		*str;
	static char		c;

	if (bits < 1)
		str = ft_calloc(len + 1, sizeof(char));
	if (sig == SIGUSR1)
		c |= 1 << bits;
	bits++;
	if (bits % 8 == 0)
	{
		if (chars < len)
		{
			str[chars] = c;
			chars++;
		}
		else if (chars == len)
			ft_printf("%s", str);
		c = 0;
	}
}
void signal_handler(int sig, siginfo_t *client, void *ucontext)
{
	static int		bit_len;
	static int		bits;
	static pid_t	client_id;

	if (!client_id || client_id != client->si_pid)
	{
		client_id = client->si_pid;
		bits = 0;
	}
	if (bits < 32)
	{
		bit_len = bit_len << 1;
		if (sig == SIGUSR1)
			bit_len |= 1;
		bits++;
	}
	if (bits == 32)
	{
		message_receiver(sig, bit_len);
	}
}

int	main(int argc, char **argv)
{
	struct sigaction	sa;

	ft_memset(sa, 0, sizeof(sa));
	ft_printf("Server ID:%d", pid());

	sa.sa_sigaction = signal_handler;
	sa.sa_flags = SA_SIGINFO;

	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
	{
		ft_printf("Running...");
		sleep(1);
	}
	
}