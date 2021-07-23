/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_forline.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaryjan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 07:27:09 by mmaryjan          #+#    #+#             */
/*   Updated: 2021/04/24 07:27:12 by mmaryjan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_shlvlinc(t_com *com)
{
	int		temp2;
	char	*temps;

	temp2 = ft_atoi(com->env->content);
	temp2++;
	com->fork = temp2;
	temps = com->env->content;
	com->env->content = ft_itoa(temp2);
	free(temps);
	temps = NULL;
}

void	ft_oldpwd(t_com *com)
{
	com->env->content = NULL;
	com->oldpwd = com->env->content;
}

void	ft_curpwd(t_com *com)
{
	char	*temps;
	char	temp3[300];

	temps = com->env->content;
	com->env->content = ft_strdup(getcwd(temp3, 300));
	free(temps);
	temps = NULL;
	com->curpwd = com->env->content;
}

void	ft_shlvl(t_com *com)
{
	t_env	*temp;

	temp = com->env;
	while (com->env)
	{
		if (!(ft_strcmp(com->env->key, "SHLVL")))
			ft_shlvlinc(com);
		if (!(ft_strcmp(com->env->key, "OLDPWD")))
			ft_oldpwd(com);
		if (!(ft_strcmp(com->env->key, "PWD")))
			ft_curpwd(com);
		com->env = com->env->next;
	}
	com->env = temp;
	ft_copyenvp(com);
}
