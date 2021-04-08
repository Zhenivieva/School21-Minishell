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

t_list	*ft_lstnew(void *content, int type)
{
	t_list *str;

	str = malloc(sizeof(t_list));
	if (!str)
		return (NULL);
	str->type = type;
    str->content = content;
	str->next = 0x0;
	return (str);
}

t_env	*ft_lstnew1(char *key, char *content)
{
	t_env *str;

	str = malloc(sizeof(t_env));
	if (!str)
		return (NULL);
	str->key = key;
	str->content = content;
	str->next = 0x0;
	return (str);
}

t_list	*ft_lstlast(t_list *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
	{
		lst = lst->next;
	}
	return (lst);
}

t_env	*ft_lstlast1(t_env *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
	{
		lst = lst->next;
	}
	return (lst);
}

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list *last;

	if (!lst || !new)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	last = ft_lstlast(*lst);
	new->next = last->next;
	last->next = new;
}

void	ft_lstadd_back1(t_env **lst, t_env *new)
{
	t_env *last;

	if (!lst || !new)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	last = ft_lstlast1(*lst);
	new->next = last->next;
	last->next = new;
}
