/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mflor <mflor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/17 23:52:41 by mflor             #+#    #+#             */
/*   Updated: 2021/04/24 03:13:25 by mflor            ###   ########.fr       */
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

void	ft_copyenvp(t_com *com)
{
	t_env	*temp;
	int		t;
	char	*temp2;

	temp = com->env;
	com->envp = malloc(sizeof(char *) * (ft_lstsize(com->env) + 1));
	if (!(com && com->envp))
		ft_error(-2);
	ft_lstadd_front_m(&g_mem, ft_lstnew_m1(com->envp, 0));
	t = -1;
	while (com->env)
	{
		temp2 = ft_strjoin("=", com->env->content);
		com->envp[++t] = ft_strjoin_f(com->env->key, temp2);
		com->env = com->env->next;
	}
	com->envp[++t] = NULL;
	com->env = temp;
}

int		ft_errno(char *komand, int ex, t_com *com)
{
	ft_putstr_fd("minishell: ", 1);
	ft_putstr_fd(komand, 1);
	ft_putstr_fd(": command not found\n", 1);
	com->exit = ex + 128;
	exit(com->exit);
}
