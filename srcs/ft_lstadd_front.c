/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaryjan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 17:43:39 by mmaryjan          #+#    #+#             */
/*   Updated: 2021/02/25 21:23:52 by mmaryjan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//для malloc/free

#include "minishell.h"

t_list	*ft_lstnew(void *content)
{
	t_list *str;

	str = malloc(sizeof(t_list));
	if (!str)
		return (NULL);
	str->content = content;
	str->next = 0x0;
	return (str);
}

void	ft_lstclear(t_list **lst)
{
	t_list *lst11;
	t_list *lst22;

	if (!lst)
		return ;
	lst11 = *lst;
	while (lst11)
	{
		lst22 = lst11->next;
		if (lst11 && lst11->content)
			free(lst11->content);
		lst11->content = NULL;
		if (lst11)
			free(lst11);
		lst11 = NULL;
		lst11 = lst22;
	}
	*lst = NULL;
}

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (!lst || !new)
		return ;
	new->next = *lst;
	*lst = new;
}

void	free_and_null(void **ptr)
{
	if (*ptr)
		free(*ptr);
	*ptr = NULL;
}
