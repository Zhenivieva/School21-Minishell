/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaryjan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 22:16:20 by mmaryjan          #+#    #+#             */
/*   Updated: 2020/11/06 00:51:03 by mmaryjan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	ls1;
	char	*dest;
	size_t	i;

	if (set == 0 || s1 == 0)
		return ((char*)s1);
	while (*s1 && ft_strchr(set, *s1))
		s1++;
	ls1 = ft_strlen(s1);
	i = 0;
	while (i < ls1)
	{
		if (!ft_strchr(set, s1[ls1 - 1 - i]))
			break ;
		i++;
	}
	dest = malloc(sizeof(char) * (ls1 - i + 1));
	if (dest == NULL)
		return (NULL);
	ft_lstadd_front_m(&g_mem, ft_lstnew(dest, 0));
	dest = ft_memcpy(dest, s1, ls1 - i);
	dest[ls1 - i] = '\0';
	return (dest);
}
