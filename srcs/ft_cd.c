/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaryjan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/17 23:59:53 by mmaryjan          #+#    #+#             */
/*   Updated: 2021/04/17 23:59:55 by mmaryjan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_copypwd2(t_com *com)
{
	char	*temp;
	t_env	*temp2;

	temp2 = com->env;
	while (com->env)
	{
		if (!(ft_strcmp(com->env->key, "PWD")))
		{
			temp = com->env->content;
			com->env->content = ft_strdup(com->curpwd);
			free(temp);
		}
		if (!(ft_strcmp(com->env->key, "OLDPWD")))
		{
			temp = com->env->content;
			com->env->content = ft_strdup(com->oldpwd);
			free(temp);
		}
		com->env = com->env->next;
	}
	com->env = temp2;
}

void	ft_copypwd(t_com *com)
{
	int		t;
	char	*temp;

	t = -1;
	while (com->envp[++t])
	{
		if (!(ft_strncmp(com->envp[t], "PWD", 3)))
		{
			temp = com->envp[t];
			com->envp[t] = ft_strjoin("PWD=", com->curpwd);
			free(temp);
		}
		if (!(ft_strncmp(com->envp[t], "OLDPWD", 6)))
		{
			temp = com->envp[t];
			com->envp[t] = ft_strjoin("OLDPWD=", com->oldpwd);
			free(temp);
		}
	}
	ft_copypwd2(com);
}

void	ft_cd2(t_com *com)
{
	int		flag;
	t_env	*temp;

	flag = 0;
	if (!(com->args[1]))
	{
		temp = com->env;
		while (com->env)
		{
			if (!(ft_strcmp(com->env->key, "HOME")))
			{
				if (com->env->content)
					com->args[1] = com->env->content;
				else
					write(1, "HOME isn't set\n", 15);
				flag = 1;
			}
			com->env = com->env->next;
		}
		com->env = temp;
		if (!flag)
			write(1, "HOME isn't set\n", 15);
	}
}

int		ft_cd(t_com *com)
{
	char pwd[300];

	ft_cd2(com);
	if ((chdir(com->args[1])) < 0)
	{
		ft_putstr_fd("minishell: ", 1);
		ft_putstr_fd(strerror(errno), 1);
		write(1, "\n", 1);
	}
	else
	{
		com->oldpwd = com->curpwd;
		com->curpwd = ft_strdup(getcwd(pwd, 300));
		ft_copypwd(com);
	}
	return (0);
}
