/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_mem.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaryjan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 05:01:24 by mmaryjan          #+#    #+#             */
/*   Updated: 2020/11/08 06:03:24 by mmaryjan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*ft_lstnew(char *content, int type)
{
	t_list *str;

	str = malloc(sizeof(t_list));
	if (!str)
		return (NULL);
	str->type = type;
	str->content = content;
	str->next = NULL;
	return (str);
}

t_list	*ft_lstnew_m1(void *content, int type)
{
	t_list *str;

	str = malloc(sizeof(t_list));
	if (!str)
		return (NULL);
	str->type = type;
	str->content = content;
	str->next = NULL;
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

void	ft_lstadd_front_m(t_list **lst, t_list *new)
{
	if (!lst || !new)
		return ;
	new->next = *lst;
	*lst = new;
}
