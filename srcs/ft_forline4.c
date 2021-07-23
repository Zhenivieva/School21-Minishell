/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_forline4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaryjan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 07:29:00 by mmaryjan          #+#    #+#             */
/*   Updated: 2021/04/24 07:29:02 by mmaryjan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_more(char *pipecom, t_com *com, t_indexes *inds)
{
	char	*ret;
	t_list	*new;

	if (pipecom[inds->k] == '>' && pipecom[inds->k + 1] != '>')
	{
		inds->k++;
		while (pipecom[inds->k] == ' ')
			inds->k++;
		com->konecg = 1;
		ret = ft_forcontent(pipecom + inds->k, &inds->k);
		new = ft_lstnew(ret, 2);
		ft_lstadd_back(&com->redir, new);
		com->konecg++;
	}
}

void	ft_less(char *pipecom, t_com *com, t_indexes *inds)
{
	while (pipecom[inds->k] == '<')
	{
		inds->k++;
		while (pipecom[inds->k] == ' ')
			inds->k++;
		com->konecg++;
		ft_lstadd_back(&com->redir, ft_lstnew(ft_forcontent(
				pipecom + inds->k, &inds->k), 1));
	}
}

void	ft_double_more(char *pipecom, t_com *com, t_indexes *inds)
{
	if (pipecom[inds->k] == '>' && pipecom[inds->k + 1] == '>')
	{
		inds->k = inds->k + 2;
		while (pipecom[inds->k] == ' ')
			inds->k++;
		com->konecg++;
		ft_lstadd_back(&com->redir, ft_lstnew(ft_forcontent(
				pipecom + inds->k, &inds->k), 3));
	}
	if ((pipecom[inds->k] != '<') && (pipecom[inds->k] != '>'))
		inds->k++;
}

void	ft_parsecom2(char *pipecom, t_com *com, t_indexes *inds)
{
	int		t;

	inds->k = 0;
	while (pipecom[inds->k])
	{
		inds->b = 0;
		t = 0;
		while (pipecom[inds->k] == ' ' || pipecom[inds->k]
		== '>' || pipecom[inds->k] == '<')
		{
			ft_more(pipecom, com, inds);
			ft_less(pipecom, com, inds);
			ft_double_more(pipecom, com, inds);
		}
		com->args[inds->a] = malloc(ft_numcommand(pipecom + inds->k) + 1000);
		if (com->args[inds->a] == NULL)
			ft_error(-3);
		ft_lstadd_front_m(&g_mem, ft_lstnew(com->args[inds->a], 0));
		parse_word(pipecom, com, inds);
		com->args[inds->a][inds->b] = '\0';
		if (inds->b > 0)
			inds->a++;
	}
}

void	ft_parsecom(char *pipecom, t_com *com)
{
	t_indexes	inds;

	inds.k = -1;
	inds.a = 0;
	com->args = malloc(sizeof(char *) * (ft_numargs(pipecom) + 2));
	if (!com->args)
		ft_error(4);
	ft_lstadd_front_m(&g_mem, ft_lstnew_m1(com->args, 0));
	ft_parsecom2(pipecom, com, &inds);
	com->args[inds.a] = NULL;
}
