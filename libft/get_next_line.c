/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcarrasq <hcarrasq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 11:59:54 by hcarrasq          #+#    #+#             */
/*   Updated: 2025/03/12 12:14:09 by hcarrasq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*get_next_line(int fd)
{
	char		*str;
	static char	buf [BUFFER_SIZE + 1];

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	str = NULL;
	while (buf[0] || read(fd, buf, BUFFER_SIZE) > 0)
	{
		str = ft_strjoin(buf, str);
		if (!str)
			return (NULL);
		buf_cleaner(buf);
		if (str[ft_strlen(str) - 1] == '\n')
			return (str);
	}
	return (str);
}
