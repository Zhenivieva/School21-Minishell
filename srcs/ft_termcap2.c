/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_termcap2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaryjan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 12:00:09 by mmaryjan          #+#    #+#             */
/*   Updated: 2021/04/24 12:00:12 by mmaryjan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_else2(t_com *com, char *str, int it, int it2)
{
	char	*tbuf;

	tbuf = malloc(sizeof(char) * (2000));
	ft_lstadd_front_m(&g_mem, ft_lstnew(tbuf, 0));
	while (com->buf[it] && it < com->max - 1)
	{
		if (it2 == com->count - 1)
			tbuf[it2++] = str[0];
		else
			tbuf[it2++] = com->buf[it++];
	}
	tbuf[it2] = '\0';
	free(com->buf);
	com->buf = tbuf;
	it = -1;
	while (++it < com->count - 1)
		tputs(cursor_left, 1, ft_putchar);
	write(1, com->buf, com->max);
	it = -1;
	while (++it < com->max - com->count)
		tputs(cursor_left, 1, ft_putchar);
}

void	ft_else(t_com *com, char *str, char **line, int res)
{
	if (com->flag)
		com->buf = ft_strdup(*line);
	if (ft_strcmp(str, "\n") && ft_strlen(str) == 1)
	{
		com->count++;
		com->max++;
		if (com->count == com->max)
		{
			com->buf = ft_strjoin_f(com->buf, str);
			write(1, str, res);
		}
		else
		{
			ft_else2(com, str, 0, 0);
		}
	}
	if (ft_strcmp(str, "\n"))
		*line = ft_strdup(com->buf);
}

void	ft_conds(t_com *com, char **line, char *str, int res)
{
	if (!ft_strcmp(str, "\e[A"))
		ft_up(com, line);
	else if (!ft_strcmp(str, "\e[H"))
		ft_home(com);
	else if (!ft_strcmp(str, "\e[F"))
		ft_end(com);
	else if (!ft_strcmp(str, "\e[B"))
		ft_down(com, line);
	else if (!ft_strcmp(str, "\177"))
		ft_delete(com, line);
	else if (!ft_strcmp(str, "\e[D"))
		ft_left(com);
	else if (!ft_strcmp(str, "\e[C"))
		ft_right(com);
	else if (!ft_strcmp(str, "\4"))
		ft_ctrld(com);
	else if (!ft_strcmp(str, "\3"))
		ft_ctrlc(com, line);
	else
		ft_else(com, str, line, res);
}

void	ft_cicle(t_com *com, char **line)
{
	int		res;
	char	str[2000];

	str[0] = '\0';
	com->flag = 0;
	while (ft_strcmp(str, "\n"))
	{
		res = read(0, str, 100);
		str[res] = '\0';
		if ((!ft_strcmp(str, "\t")) || (!ft_strcmp(str, "\034")))
			continue;
		ft_conds(com, line, str, res);
	}
}

void	ft_ctrld(t_com *com)
{
	if (ft_strlen(com->buf) == 0)
	{
		write(1, "exit\n", 5);
		exit(0);
	}
}
