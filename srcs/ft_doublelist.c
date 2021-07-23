/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_doublelist.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaryjan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 00:09:52 by mmaryjan          #+#    #+#             */
/*   Updated: 2021/04/18 00:10:02 by mmaryjan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_init(t_tlist **head, t_tlist **tail, char *str, t_com *com)
{
	t_tlist	*new;

	new = malloc(sizeof(t_tlist));
	if (new == NULL)
	{
		exit(2);
		return ;
	}
	new->content = ft_strdup(str);
	new->next = NULL;
	new->prev = NULL;
	*head = new;
	*tail = new;
	com->inited = 1;
	ft_lstadd_front_m(&g_mem, ft_lstnew_m1(new, 0));
}

void	insert_beginning(t_tlist **head, char *str)
{
	t_tlist	*new;

	new = malloc(sizeof(t_tlist));
	if (new == NULL)
	{
		exit(1);
		return ;
	}
	new->content = ft_strdup(str);
	new->next = *head;
	new->prev = NULL;
	if (*head != NULL)
	{
		(*head)->prev = new;
	}
	ft_lstadd_front_m(&g_mem, ft_lstnew_m1(new, 0));
	*head = new;
}
