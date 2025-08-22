/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maudiffr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 11:33:04 by maudiffr          #+#    #+#             */
/*   Updated: 2023/03/06 12:10:34 by maudiffr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s && s[i])
		i++;
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == c)
			return ((char *)s);
		s++;
	}
	if (c == '\0')
		return ((char *)s);
	return (0);
}

/* Extracts the "left" part of the string, i.e., the complete line up to
   and including the newline if present. This is the part returned by
   get_next_line.*/

char	*ft_left(char *str)
{
	int		i;
	char	*left;

	i = 0;
	while (str && str[i] && str[i] != '\n')
		i++;
	if (str && str[i] == '\n')
		i++;
	left = malloc(sizeof(char) * (i + 1));
	if (left == NULL)
		return (NULL);
	i = 0;
	while (str && str[i] && (i == 0 || str[i - 1] != '\n'))
	{
		left[i] = str[i];
		i++;
	}
	left[i] = '\0';
	return (left);
}

/* Builds the "right" part of the string, i.e., what remains after the
   returned line. Frees the old string and keeps only the leftover for
   the next call. */

char	*ft_new_str(char *str)
{
	size_t		i;
	int			j;
	char		*right;

	i = 0;
	j = 0;
	while (str && str[i] && str[i] != '\n')
		i++;
	if (str && str[i] == '\n')
		i++;
	right = malloc(sizeof(char) * (ft_strlen(str) - i + 1));
	if (right == NULL)
		return (NULL);
	while (str && str[i])
		right[j++] = str[i++];
	right[j] = '\0';
	free(str);
	return (right);
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	size_t	i;
	size_t	j;
	char	*tab;

	i = 0;
	j = 0;
	tab = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (tab == NULL)
		return (NULL);
	while (s1 && s1[i])
		tab[j++] = s1[i++];
	i = 0;
	while (s2 && s2[i])
		tab[j++] = s2[i++];
	tab[j] = '\0';
	return (tab);
}
