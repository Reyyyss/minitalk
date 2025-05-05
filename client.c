/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henrique-reis <henrique-reis@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 18:10:17 by hcarrasq          #+#    #+#             */
/*   Updated: 2025/05/04 10:03:18 by henrique-re      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int 		g_global_ack = 0;

void	action_handler(int signal)
{
	if (signal == SIGUSR1)
		g_global_ack = 1;
}

void	phrase_lenght(int pid, int lenght)
{
	int	bit;
	int	holder;
	int timeout;

	bit = 0;
	while (bit < 32)
	{
		g_global_ack = 0;
		timeout = 1000;
		holder = ((lenght >> bit) & 1);
		if (holder == 1)
			kill_checker(pid, SIGUSR1);
		else
			kill_checker(pid, SIGUSR2);
	while (g_global_ack == 0 && timeout-- > 0) 
		usleep(50);
	if (timeout == 0) 
	{
		ft_printf("Timeout waiting for acknowledgment\n");
		exit(1);
	}
		bit++;
	}
}

void	message_convertor(int pid, char c)
{
	int	bit;
	int timeout;

	bit = 0;
	while (bit < 8)
	{
		g_global_ack = 0;
		timeout = 1000;
		if ((c >> bit) & 1)
			kill_checker(pid, SIGUSR1);
		else
			kill_checker(pid, SIGUSR2);
		while (g_global_ack == 0 && timeout-- > 0)
			usleep(50);
		if (timeout == 0) 
		{
			ft_printf("Timeout waiting for acknowledgment\n");
			exit(1);
		}
		bit++;
	}
}

int	main(int argc, char **argv)
{
	int					server_id;
	int					i;
	struct sigaction	sa;
	size_t				lenght;

	i = -1;
	lenght = ft_strlen(argv[2]);
	if (argc != 3)
		return(ft_putstr_fd("Usage: ./client <server_pid> <message>", 2), 1);
	sa.sa_handler = &action_handler;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	server_id = ft_atoi(argv[1]);
	if (server_id <= 0)
	{
		perror("id is not valid\n");
		exit(1);
	}
	phrase_lenght(server_id, lenght);
	while (argv[2][++i])
		message_convertor(ft_atoi(argv[1]), argv[2][i]);
	message_convertor('\0', server_id);
	ft_printf("Message sended\n");
}
