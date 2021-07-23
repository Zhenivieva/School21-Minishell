/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaryjan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 03:17:39 by mmaryjan          #+#    #+#             */
/*   Updated: 2021/04/24 03:17:50 by mmaryjan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env2(t_com *com)
{
	if (!(ft_strcmp(com->args[1], "PWD")))
		ft_pwd();
	else if (!(ft_strcmp(com->args[1], "LOGNAME")))
	{
		while (com->env)
		{
			if (!(ft_strcmp(com->env->key, "LOGNAME")))
			{
				ft_putstr_fd(com->env->content, 1);
				write(1, "\n", 1);
			}
			com->env = com->env->next;
		}
	}
	else
	{
		write(1, "env: ", 5);
		ft_putstr_fd(com->args[1], 1);
		write(1, ": No such file or directory\n", 28);
	}
}

int		ft_env(t_com *com)
{
	t_env	*temp;

	temp = com->env;
	if (!(com->args[1]))
	{
		while (com->env)
		{
			if (com->env->content)
			{
				ft_putstr_fd(com->env->key, 1);
				write(1, "=", 1);
				ft_putstr_fd(com->env->content, 1);
				write(1, "\n", 1);
			}
			com->env = com->env->next;
		}
		com->env = temp;
		write(1, "_=/usr/bin/env\n", 15);
	}
	else
	{
		ft_env2(com);
		com->env = temp;
	}
	return (0);
}
