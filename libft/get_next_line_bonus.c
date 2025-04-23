/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcarrasq <hcarrasq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 14:37:31 by hcarrasq          #+#    #+#             */
/*   Updated: 2025/02/03 17:17:37 by hcarrasq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*get_next_line(int fd)
{
	char		*str;
	static char	buf [FOPEN_MAX][BUFFER_SIZE + 1];

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > FOPEN_MAX)
		return (NULL);
	str = NULL;
	while (buf[fd][0] || read(fd, buf[fd], BUFFER_SIZE) > 0)
	{
		str = ft_strjoin(buf[fd], str);
		if (!str)
			return (NULL);
		buf_cleaner(buf[fd]);
		if (str[ft_strlen(str) - 1] == '\n')
			return (str);
	}
	return (str);
}

/* int main()
{
	int i = 0;
	
	int fd = open("test.txt", O_RDONLY);
	int fd2 = open("test2.txt", O_RDONLY);
	while (i < 5)
	{
		printf("%s\n", get_next_line(fd2));
		printf("%s\n", get_next_line(fd));
		i++;
	}
	return 0;
} */