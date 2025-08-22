/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maudiffr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 09:42:30 by maudiffr          #+#    #+#             */
/*   Updated: 2023/03/23 10:21:35 by maudiffr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/* Reads chunks from the file (BUFFER_SIZE bytes) and appends them to the
   existing leftover string. Stops reading when a newline is found or
   when there is nothing left to read. */

char	*read_and_join(int fd, char *str)
{
	int			ret;
	char		buf[BUFFER_SIZE + 1];
	char		*temp;

	ret = BUFFER_SIZE;
	while (ret > 0)
	{
		ret = read(fd, buf, BUFFER_SIZE);
		if (ret == -1)
		{
			free(str);
			return (NULL);
		}
		if (ret == 0)
			break ;
		buf[ret] = '\0';
		temp = str;
		str = ft_strjoin(temp, buf);
		free(temp);
		if (ft_strchr(str, '\n'))
			break ;
	}
	return (str);
}

/* Main function that reads from a file descriptor and returns the next line.
   It uses a static variable to keep track of leftover data between calls.
   Return NULL when the end of file is reached or an error. */

char	*get_next_line(int fd)
{
	char		*line;
	static char	*str;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	str = read_and_join(fd, str);
	line = ft_left(str);
	str = ft_new_str(str);
	if (line[0] == '\0' && str[0] == '\0')
	{
		free(str);
		free(line);
		str = NULL;
		return (NULL);
	}
	return (line);
}
