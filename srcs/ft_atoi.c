/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaryjan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 20:21:34 by mmaryjan          #+#    #+#             */
/*   Updated: 2020/11/05 20:21:39 by mmaryjan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_atoi(const char *str)
{
	long	atoi;
	int		k;

	k = 1;
	atoi = 0;
	while ((*str == ' ') || (*str == '\f') || (*str == '\r')
		|| (*str == '\t') || (*str == '\v') || (*str == '\n'))
		str++;
	if ((*str == '+') || (*str == '-'))
	{
		if (*str == '-')
			k = -k;
		str++;
	}
	while ((*str >= '0') && (*str <= '9') && atoi <= 2147483648)
	{
		atoi = atoi * 10 + (*str - 48);
		str++;
	}
	if (atoi > 2147483648 && k == -1)
		return (53);
	if (atoi > 2147483647 && k == 1)
		return (-1);
	return (atoi * k);
}
