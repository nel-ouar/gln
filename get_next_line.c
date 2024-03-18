/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-ouar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 13:05:17 by nel-ouar          #+#    #+#             */
/*   Updated: 2024/03/14 00:50:44 by nel-ouar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_rest(char	*str)
{
	int			i;
	int			j;
	char		*res;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i] != '\0' && str[i] != '\n')
		i++;
	if (str[i] == '\0')
	{
		free(str);
		return (NULL);
	}
	res = malloc(ft_strlen(str) - i + 1);
	if (!res)
		return (NULL);
	if (str[i] == '\n')
		i++;
	j = 0;
	while (str[i] != '\0')
		res[j++] = str[i++];
	res[j] = '\0';
	free(str);
	return (res);
}

char	*ft_gnl(char *str)
{
	int			i;
	int			j;
	char		*line;

	i = 0;
	j = 0;
	if (!str)
		return (NULL);
	while (str[i] != '\0' && str[i] != '\n')
		i++;
	if (str[i])
		i++;
	line = malloc(i + 1);
	if (!line)
		return (NULL);
	i = 0;
	while (str[i] != '\0' && str[i] != '\n')
		line[j++] = str[i++];
	if (str[i] == '\n')
		line[j++] = '\n';
	line[j] = '\0';
	return (line);
}

char	*ft_gnl_read(int fd, char *str)
{
	char	*tmp;
	int		i;

	if (!str)
		str = ft_strdup("");
	i = 1;
	tmp = malloc(BUFFER_SIZE + 1);
	if (!tmp)
		return (NULL);
	while (i && !ft_strchr(str, '\n'))
	{
		i = read(fd, tmp, BUFFER_SIZE);
		if (i == -1 || (i == 0 && !str[0]))
		{
			free(tmp);
			free(str);
			return (NULL);
		}
		tmp[i] = '\0';
		str = ft_strjoin(str, tmp);
		if (!str)
			return (NULL);
	}
	free(tmp);
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*b;
	char		*l;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	b = ft_gnl_read(fd, b);
	if (!b)
		return (NULL);
	l = ft_gnl(b);
	b = ft_rest(b);
	return (l);
}
