/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaryjan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 12:12:55 by mmaryjan          #+#    #+#             */
/*   Updated: 2020/11/06 18:53:40 by mmaryjan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char		*filldest(char *dest, int n, size_t len)
{
	int	i;

	i = 0;
	if (n < 0)
	{
		dest[0] = '-';
		n = -n;
	}
	if (n == 0)
		dest[0] = '0';
	while (n)
	{
		dest[len - i - 1] = n % 10 + 48;
		n = n / 10;
		i++;
	}
	dest[len] = '\0';
	return (dest);
}

static size_t	retlen(int n)
{
	size_t len;

	len = 0;
	if (n < 0 || n == 0)
		len++;
	while (n)
	{
		len++;
		n = n / 10;
	}
	return (len);
}

char			*ft_itoa(int n)
{
	size_t	len;
	char	*dest;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	len = retlen(n);
	dest = malloc(sizeof(char) * (len + 1));
	if (!dest)
		return (NULL);
	ft_lstadd_front_m(&g_mem, ft_lstnew(dest, 0));
	dest = filldest(dest, n, len);
	return (dest);
}
