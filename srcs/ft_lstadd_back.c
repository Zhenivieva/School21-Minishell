/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaryjan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 05:01:24 by mmaryjan          #+#    #+#             */
/*   Updated: 2020/11/08 06:03:24 by mmaryjan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*ft_lstnew1(char *key, char *content)
{
	t_env *str;

	str = malloc(sizeof(t_env));
	if (!str)
		return (NULL);
	str->key = key;
	str->content = content;
	str->next = 0x0;
	ft_lstadd_front_m(&g_mem, ft_lstnew_m1(str, 0));
	return (str);
}

void	ft_lstadd_front(t_env **lst, t_env *new)
{
	if (!lst || !new)
		return ;
	new->next = *lst;
	*lst = new;
}

void	ft_insafter(t_env *env, t_env *new)
{
	new->next = env->next;
	env->next = new;
}

void	ft_putsorted(t_env **lst, t_env *new)
{
	t_env *curr;

	if (*lst == NULL || ft_strncmp((*lst)->key, new->key,
								ft_strlen(new->key)) >= 0)
	{
		ft_lstadd_front(lst, new);
		return ;
	}
	curr = *lst;
	while (curr->next)
	{
		if (ft_strncmp(curr->next->key, new->key, ft_strlen(curr->key)) >= 0)
		{
			ft_insafter(curr, new);
			return ;
		}
		curr = curr->next;
	}
	ft_insafter(curr, new);
}
