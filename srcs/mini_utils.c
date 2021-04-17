/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mflor <mflor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/17 23:52:41 by mflor             #+#    #+#             */
/*   Updated: 2021/04/17 23:56:47 by mflor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_lstsize(t_env *lst)
{
	int	size;

	size = 0;
	while (lst != NULL)
	{
		lst = lst->next;
		size++;
	}
	return (size);
}

int		ft_kolenvp(char **envp)
{
	int t;
	int c;

	t = -1;
	c = 0;
	while (envp[++t])
		c++;
	return (c);
}

void	ft_copyenvp(t_com *com)
{
	t_env	*temp;
	int		t;
	char	*temp2;

	temp = com->env;
	com->envp = malloc(sizeof(char *) * (ft_lstsize(com->env) + 1));
	if (!(com && com->envp))
		ft_error(-2);
	t = -1;
	while (com->env)
	{
		temp2 = ft_strjoin("=", com->env->content);
		com->envp[++t] = ft_strjoin_f(com->env->key, temp2);
//		free (temp2); //to clean leak, but it segs with this srting
		com->env = com->env->next;
	}
	com->envp[++t] = NULL;
	com->env = temp;
}

void	ft_forcat(char **args)
{
	if (!(ft_strcmp(args[0], "cat")))
		if (!(args[1]))
			g_p[0] = 1;
}
