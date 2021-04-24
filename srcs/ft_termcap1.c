/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_termcap1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaryjan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 11:59:59 by mmaryjan          #+#    #+#             */
/*   Updated: 2021/04/24 12:00:02 by mmaryjan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_home(t_com *com)
{
	while (com->count > 0)
	{
		tputs(cursor_left, 1, ft_putchar);
		com->count--;
	}
}

void	ft_end(t_com *com)
{
	while (com->count < com->max)
	{
		tputs(cursor_right, 1, ft_putchar);
		com->count++;
	}
}

void	ft_delete(t_com *com, char **line)
{
	if (com->count > 0)
	{
		tputs(cursor_left, 1, ft_putchar);
		tputs(tgetstr("dc", 0), 1, ft_putchar);
		com->buf = ft_remove(com->buf, com->count - 1);
		*line = ft_strdup(com->buf);
		com->count--;
		com->max--;
	}
}

void	ft_left(t_com *com)
{
	if (com->count > 0)
	{
		tputs(cursor_left, 1, ft_putchar);
		com->count--;
	}
}

void	ft_right(t_com *com)
{
	if (com->count < com->max)
	{
		tputs(cursor_right, 1, ft_putchar);
		com->count++;
	}
}
