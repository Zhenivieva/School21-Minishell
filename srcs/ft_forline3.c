/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_forline3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaryjan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 07:29:00 by mmaryjan          #+#    #+#             */
/*   Updated: 2021/04/24 07:29:02 by mmaryjan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_numcommand(char *command)
{
	int	t;
	int	c;

	c = 0;
	t = -1;
	if (!command)
		return (0);
	while (command[++t] != '\0' && command[t] != ' ')
		c++;
	return (c);
}

int		ft_numargs(char *command)
{
	int	t;
	int	c;

	c = 0;
	t = -1;
	if (!command)
		return (0);
	while (command[++t])
	{
		if (command[t] == ' ')
		{
			while (command[t] == ' ')
				t++;
			c++;
		}
	}
	return (c);
}

void	double_quotes(char *pipecom, t_com *com, t_indexes *inds)
{
	if (pipecom[inds->k] == '"')
	{
		inds->k++;
		while (pipecom[inds->k] != '"')
		{
			if (pipecom[inds->k] == '\\' && (pipecom[inds->k + 1] == '$'
				|| pipecom[inds->k + 1] == '"' || pipecom[inds->k + 1] == '\\'))
				inds->k++;
			if (pipecom[inds->k] == '$' && pipecom[inds->k - 1] == '\\')
			{
				com->args[inds->a][inds->b++] = pipecom[inds->k++];
			}
			if (pipecom[inds->k] == '$')
			{
				if (pipecom[inds->k + 1] != '\0')
					inds->k = inds->k + ft_getdollar(pipecom
						+ inds->k + 1, com, inds);
				continue;
			}
			if (pipecom[inds->k] != '$')
				com->args[inds->a][inds->b++] = pipecom[inds->k++];
		}
		inds->k++;
	}
}

void	ft_forenv(t_com *com, char **envp)
{
	int		t;
	char	**envstring;

	com->env = NULL;
	t = -1;
	while (envp[++t])
	{
		envstring = ft_split(envp[t], '=');
		ft_putsorted(&com->env, ft_lstnew1(envstring[0], envstring[1]));
	}
	ft_shlvl(com);
}
