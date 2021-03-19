/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaryjan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 03:42:39 by mmaryjan          #+#    #+#             */
/*   Updated: 2020/11/21 03:42:49 by mmaryjan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_next_line.h"

char	*ft_strchr(const char *s, int c)
{
	char	cc;

	cc = (char)c;
	while (*s)
	{
		if (*s == cc)
			return ((char*)s);
		s++;
	}
	if (*s == cc)
		return ((char*)s);
	return ((char*)NULL);
}

char	*ft_save(char *buf, char *ost)
{
	char *copy;

	if (ost)
	{
		copy = ft_strjoin(ost, buf);
		free(ost);
		ost = ft_strdup(copy);
		free(copy);
	}
	else
		ost = ft_strdup(buf);
	return (ost);
}

char	*ft_check_line(char *ost, char **line, int resread)
{
	unsigned int	i;
	char			*copy;

	i = 0;
	while (ost[i])
	{
		if (ost[i] == '\n')
			break ;
		i++;
	}
	if (i < ft_strlen(ost))
	{
		*line = ft_substr(ost, 0, i);
		copy = ft_substr(ost, i + 1, ft_strlen(ost));
		free(ost);
		ost = ft_strdup(copy);
		free(copy);
	}
	else if (resread == 0)
	{
		*line = ost;
		ost = NULL;
	}
	return (ost);
}

int		retresread(char **ost, int fd)
{
	char	*buf;
	int		resread;

	if (!(buf = malloc(sizeof(char) * (BUFFER_SIZE + 1))))
		return (-1);
	while (!ft_strchr(*ost, '\n') && (resread = read(fd, buf, BUFFER_SIZE)))
	{
		if (resread == -1)
		{
			free(buf);
			buf = NULL;
			return (-1);
		}
		buf[resread] = '\0';
		*ost = ft_save(buf, *ost);
		if (ft_strchr(buf, '\n'))
			break ;
	}
	free(buf);
	buf = NULL;
	return (resread);
}

int		get_next_line(int fd, char **line)
{
	static char	*ost[4096];
	int			resread;

	if (fd < 0 || !line || BUFFER_SIZE <= 0)
		return (-1);
	if (!ost[fd] && !(ost[fd] = ft_strdup("")))
		return (-1);
	if ((resread = retresread(&ost[fd], fd)) == -1)
		return (-1);
	if (resread <= 0 && !ost[fd])
	{
		*line = ft_strdup("");
		return (resread);
	}
	ost[fd] = ft_check_line(ost[fd], line, resread);
	if (resread <= 0 && !ost[fd])
		return (resread);
	return (1);
}
