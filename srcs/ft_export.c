/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaryjan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 03:17:39 by mmaryjan          #+#    #+#             */
/*   Updated: 2021/04/24 03:17:50 by mmaryjan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_poiskkey(t_env *env, char *find, char *content)
{
	t_env *temp;

	temp = env;
	while (env)
	{
		if (!(ft_strcmp(env->key, find)))
		{
			env->content = ft_strdup(content);
			env = temp;
			return (0);
		}
		env = env->next;
	}
	env = temp;
	return (1);
}

int		ft_parsearg(char *key)
{
	if ((*key <= '9' && *key >= '0') || *key == '=')
	{
		write(1, "minishell: export: `", 20);
		ft_putstr_fd(key, 1);
		write(1, "' : not a valid identifier\n", 28);
		return (0);
	}
	return (1);
}

void	ft_export2(t_com *com, t_env *temp)
{
	char	**envstring;
	int		t;

	t = 0;
	while (com->args[++t])
	{
		if (ft_parsearg(com->args[t]))
		{
			envstring = ft_split(com->args[t], '=');
			if (ft_poiskkey(com->env, envstring[0], envstring[1]))
				ft_putsorted(&com->env, ft_lstnew1(envstring[0],
		envstring[1]));
			com->env = temp;
		}
	}
	ft_copyenvp(com);
}

int		ft_export(t_com *com)
{
	t_env	*temp;

	temp = com->env;
	if (!(com->args[1]))
	{
		while (com->env)
		{
			write(1, "declare -x ", 11);
			ft_putstr_fd(com->env->key, 1);
			if (com->env->content)
			{
				write(1, "=\"", 2);
				ft_putstr_fd(com->env->content, 1);
				write(1, "\"", 1);
			}
			write(1, "\n", 1);
			com->env = com->env->next;
		}
		com->env = temp;
	}
	else
		ft_export2(com, temp);
	ft_copyenvp(com);
	return (0);
}
