/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaryjan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 21:50:08 by mmaryjan          #+#    #+#             */
/*   Updated: 2020/11/21 02:41:51 by mmaryjan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_next_line.h"

size_t	ft_strlen(const char *str)
{
	int	k;

	k = 0;
	while (*str)
	{
		k++;
		str++;
	}
	return (k);
}

char	*ft_strdup(const char *s1)
{
	char	*s2;
	size_t	len;

	len = ft_strlen(s1) + 1;
	s2 = malloc(sizeof(char) * (len));
	if (!s2)
		return (NULL);
	s2 = ft_memcpy(s2, s1, len);
	return (s2);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	const char	*src2;
	char		*dst2;

	dst2 = (char*)dst;
	src2 = (const char*)src;
	if (!n || dst == src)
		return (dst);
	while (n--)
	{
		*dst2++ = *src2++;
	}
	return (dst);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	l1;
	size_t	l2;
	char	*dest;

	if (!s1)
		return ((char*)s2);
	if (!s2)
		return ((char*)s1);
	l1 = ft_strlen(s1);
	l2 = ft_strlen(s2);
	dest = malloc(sizeof(char) * (l1 + l2 + 1));
	if (dest == NULL)
		return (NULL);
	(void)ft_memcpy(dest, s1, l1);
	(void)ft_memcpy(&dest[l1], s2, l2);
	dest[l1 + l2] = '\0';
	return (dest);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*sdest;

	sdest = malloc(sizeof(char) * (len + 1));
	if (!sdest || s == 0)
		return (NULL);
	if ((size_t)start >= ft_strlen(s))
	{
		*sdest = '\0';
		return (sdest);
	}
	i = 0;
	while (*s && (i < len))
	{
		*(sdest + i) = *(s + start + i);
		i++;
	}
	*(sdest + i) = '\0';
	return (sdest);
}
