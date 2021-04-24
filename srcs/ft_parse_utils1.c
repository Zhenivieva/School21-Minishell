/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_utils1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaryjan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 12:31:08 by mmaryjan          #+#    #+#             */
/*   Updated: 2021/04/24 12:31:11 by mmaryjan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_fillredir(t_com *com, char *pipecom, int indsk, int type)
{
	if (type == 3)
		indsk++;
	indsk++;
	while (pipecom[indsk] == ' ')
		indsk++;
	com->konecg++;
	ft_lstadd_back(&com->redir,
	ft_lstnew(ft_forcontent(pipecom + indsk, &indsk), type));
	return (1);
}

int		ft_thirdelse(t_com *com, char *pipecom, t_indexes *inds)
{
	if (pipecom[inds->k] == '<')
		if (ft_fillredir(com, pipecom, inds->k, 1))
			return (1);
	if (pipecom[inds->k] == '>' && pipecom[inds->k + 1] == '>')
		if (ft_fillredir(com, pipecom, inds->k, 3))
			return (1);
	if (pipecom[inds->k] == '>' && pipecom[inds->k + 1] != '>')
		if (ft_fillredir(com, pipecom, inds->k, 2))
			return (1);
	return (0);
}

void	ft_firstelse(t_com *com, char *pipecom, t_indexes *inds)
{
	while (pipecom[++inds->k] != '\'')
		com->args[inds->a][inds->b++] = pipecom[inds->k];
	inds->k++;
}

int		ft_kavredir(char *s, int t, int *indk, char *ret)
{
	int k;

	k = 0;
	if (s[t] == '"')
	{
		while (s[++t] != '"')
		{
			ret[k++] = s[t];
			(*indk)++;
		}
		(*indk)++;
		return (0);
	}
	else if (s[t] == '\'')
	{
		while (s[++t] != '\'')
		{
			ret[k++] = s[t];
			(*indk)++;
		}
		(*indk)++;
		return (0);
	}
	return (1);
}

int		ft_findkey(t_com *com, char *d, t_indexes *inds, int *ret)
{
	int		c;
	int		perem;
	t_env	*temp;
	int		t;

	c = 0;
	while (d[c] != '\0' && d[c] != '$' && d[c] != '\\' && d[c] != '\''
		&& d[c] != '"' && d[c] != ' ')
		c++;
	*ret = d[c] == '\\' ? c + 1 : c;
	temp = com->env;
	t = 0;
	while (com->env)
	{
		if (!(ft_strncmp(com->env->key, d,
			(ft_strlen(com->env->key) > c ? (ft_strlen(com->env->key)) : c))))
		{
			perem = 1;
			while (com->env->content[t])
				com->args[inds->a][inds->b++] = com->env->content[t++];
		}
		com->env = com->env->next;
	}
	com->env = temp;
	return (perem);
}
