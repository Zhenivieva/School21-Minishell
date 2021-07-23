/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_termcap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaryjan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 12:00:15 by mmaryjan          #+#    #+#             */
/*   Updated: 2021/04/24 12:00:17 by mmaryjan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_upconds(t_com *com)
{
	if (!(com->inited))
	{
		com->thead2 = com->head;
		com->head = com->thead;
		ft_init(&com->head, &com->tail, com->buf, com);
		com->head = com->thead2;
	}
	else
	{
		com->thead2 = com->head;
		com->head = com->thead;
		insert_beginning(&com->head, com->buf);
		com->head = com->thead2;
	}
	free(com->buf);
	com->buf = NULL;
}

void	ft_up(t_com *com, char **line)
{
	tputs(restore_cursor, 1, ft_putchar);
	tputs(tigetstr("ed"), 1, ft_putchar);
	if (com->head)
	{
		if (com->head->next && com->flag == 1)
			com->head = com->head->next;
		*line = ft_strdup(com->head->content);
		write(1, com->head->content, ft_strlen(com->head->content));
		com->flag = 1;
		com->buf = ft_strdup(*line);
		com->count = ft_strlen(*line);
		com->max = com->count;
	}
}

void	ft_down(t_com *com, char **line)
{
	tputs(restore_cursor, 1, ft_putchar);
	tputs(tigetstr("ed"), 1, ft_putchar);
	if (com->head)
	{
		if (com->head->prev)
		{
			com->head = com->head->prev;
			write(1, com->head->content, ft_strlen(com->head->content));
			*line = ft_strdup(com->head->content);
		}
		else
		{
			*line = ft_strdup("");
			com->flag = 0;
		}
	}
}

void	ft_ctrlc(t_com *com, char **line)
{
	free(*line);
	*line = NULL;
	free(com->buf);
	com->buf = NULL;
	write(1, "\nminishell$", 11);
}
