/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maudiffr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 11:23:43 by maudiffr          #+#    #+#             */
/*   Updated: 2023/03/23 10:21:57 by maudiffr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*read_and_join(int fd, char *str)
{
	int		ret;
	char	buf[BUFFER_SIZE + 1];
	char	*temp;

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

char	*get_next_line(int fd)
{
	char		*line;
	static char	*str[4096];

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	str[fd] = read_and_join(fd, str[fd]);
	line = ft_left(str[fd]);
	str[fd] = ft_new_str(str[fd]);
	if (line[0] == '\0' && str[fd][0] == '\0')
	{
		free(str[fd]);
		free(line);
		str[fd] = NULL;
		return (NULL);
	}
	return (line);
}
