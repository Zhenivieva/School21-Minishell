/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaryjan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 20:26:20 by mmaryjan          #+#    #+#             */
/*   Updated: 2020/11/05 20:26:24 by mmaryjan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*src2;
	unsigned char	*dst2;
	size_t			i;

	if (dst == NULL && src == NULL)
		return (dst);
	src2 = (unsigned char*)src;
	dst2 = (unsigned char*)dst;
	if (len == 0)
		return (dst);
	if (src < dst)
	{
		i = 0;
		while (i < len)
		{
			dst2[len - i - 1] = src2[len - i - 1];
			i++;
		}
	}
	else
	{
		while (len--)
			*dst2++ = *src2++;
	}
	return (dst);
}
