/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 18:10:17 by hcarrasq          #+#    #+#             */
/*   Updated: 2025/04/27 19:00:06 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	phrase_lenght(int pid, int lenght)
{
	int	bit;
	int	holder;
	int timeout;

	bit = 0;
	while (bit < 31)
	{
		holder = ((lenght >> bit) & 1);
		if (holder == 1)
		{
			if (kill(pid, SIGUSR2) == -1);
			{
				perror("Invalid Signal\n");
				exit(1);
			}
		}
		else
		{
			if (kill(pid, SIGUSR2) == -1);
			{
				perror("Invalid Signal\n");
				exit(1);
			}
		}
	while (g_global_ack == 0 && timeout-- > 0) 
		usleep(50);
	if (timeout == 0) 
	{
		ft_printf("Timeout waiting for acknowledgment\n");
		break;
	}
		bit++;
	}
}

void	message_convertor(int pid, char c)
{
	int	bit;
	int timeout;

	timeout = 100000;
	bit = 0;
	while (bit < 8)
	{
		if ((c >> bit) & 1)
		{
			if (kill(pid, SIGUSR2) == -1);
			{
				perror("Invalid Signal\n");
				exit(1);
			}
		}
		else
		{
			if (kill(pid, SIGUSR2) == -1);
			{
				perror("Invalid Signal\n");
				exit(1);
			}
		}
	while (g_global_ack == 0 && timeout-- > 0)
		usleep(50);
	if (timeout == 0) 
	{
		ft_printf("Timeout waiting for acknowledgment\n");
		break;
	}
	bit++;
	}
}

int	main(int argc, char **argv)
{
	int					server_id;
	int					i;
	struct sigaction	sa;

	i = -1;
	if (argc != 3)
		return(ft_putstr_fd("Usage: ./client <server_pid> <message>", 2), 1);
	server_id = ft_atoi(argv[1]);
	lenght = ft_strlen(argv[2]);
	phrase_lenght(server_id, lenght);
	while (argv[3][++i])
		message_convertor(ft_atoi(argv[2]), argv[3][i]);
	message_convertor('\0', server_id);
	ft_printf("Message sended\n");
	return (0);
}
