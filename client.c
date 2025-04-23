/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcarrasq <hcarrasq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 18:10:17 by hcarrasq          #+#    #+#             */
/*   Updated: 2025/04/23 19:29:44 by hcarrasq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	message_convertor(int pid, char c)
{
	int	bit;

	bit = 0;
	while (bit < 8)
	{
		if ((c >> bit) & 1)
		{
			if (kill(pid, SIGUSR2));
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
		usleep(500);
		bit++;
	}
}

int	main(int argc, char **argv)
{
	int	i;

	i = -1;
	if (argc != 3)
		write (2, "Error\n", 7);
	while (argv[3][++i])
		message_convertor(ft_atoi(argv[2]), argv[3][i]);
	ft_printf("Message sended\n");
	return (0);
	
}