/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_forline5.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaryjan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 07:29:00 by mmaryjan          #+#    #+#             */
/*   Updated: 2021/04/24 07:29:02 by mmaryjan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		redir_sign(char *line, int *t, int *p)
{
	*p = *t;
	*p = *p + 1;
	if (line[*p] == '>')
		*p = *p + 1;
	while (line[*p] == ' ')
		*p = *p + 1;
	if (line[*p] == '\0' || line[*p] == ';' || line[*p] == '|')
		return (-7);
	return (1);
}

int		dquotes(char *line, int *t)
{
	while (line[++(*t)] != '"')
	{
		if (line[*t] == '\\')
			*t = *t + 1;
		if (line[*t] == '\0')
			return (-1);
	}
	return (1);
}

int		sign_k(char *line, int *t, int *p, char k)
{
	line[*t] = 10;
	*p = *t;
	(*p)++;
	while (line[*p] == ' ')
		(*p)++;
	if (k == '|')
		if (line[*p] == '\0' || line[*p] == k)
			return (-8);
	if (k == ';')
		if (line[*p] == k)
			return (-8);
	return (1);
}

int		ft_forsplit2(char *line, char k)
{
	int	t;
	int	p;

	t = -1;
	while (line[++t])
	{
		if (line[t] == '<' || (line[t] == '>' && line[t + 1] != '>')
		|| (line[t] == '>' && line[t + 1] == '>'))
			if (redir_sign(line, &t, &p) == -7)
				return (ft_error(-7));
		if (line[t] == '"')
			if (dquotes(line, &t) == -1)
				return (ft_error(-1));
		if (line[t] == '\'')
			while (line[++t] != '\'')
				if (line[t] == '\0')
					return (ft_error(-1));
		if (line[t] == '\\')
			t = t + 2;
		if (line[t] == k)
			if (sign_k(line, &t, &p, k) == -8)
				return (ft_error(-8));
	}
	return (1);
}

int		ft_forsplit(char *line, char k)
{
	int	t;

	if (line == NULL)
		return (0);
	t = 0;
	while (line[t] == ' ')
		t++;
	if (line[t] == k)
	{
		return (ft_error(-6));
	}
	return (ft_forsplit2(line, k));
}
