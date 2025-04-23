/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcarrasq <hcarrasq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 18:15:40 by hcarrasq          #+#    #+#             */
/*   Updated: 2025/04/23 16:05:50 by hcarrasq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void signal_handler(int sig, siginfo_t *info, void *ucontext)
{
	static int		byte_len;
	static char		byte;

	byte_len = 0;
	if (sig == SIGUSR2)
		byte |= 1 << byte_len;
	byte_len++;
	if (byte_len == 8)
	{
		write(1, byte, 1);
		byte_len = 0;
		byte = 0;
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