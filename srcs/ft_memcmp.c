/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaryjan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 20:25:25 by mmaryjan          #+#    #+#             */
/*   Updated: 2020/11/10 20:00:38 by zheniviev        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned const char *d1;
	unsigned const char *d2;
	unsigned int		i;

	d1 = s1;
	d2 = s2;
	i = 0;
	while (i++ < n)
	{
		if (*(d1 + i - 1) != *(d2 + i - 1))
			return (*(d1 + i - 1) - *(d2 + i - 1));
	}
	return (0);
}
