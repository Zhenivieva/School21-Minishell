/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lstadd_back.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaryjan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 14:28:18 by mmaryjan          #+#    #+#             */
/*   Updated: 2021/01/23 14:28:20 by mmaryjan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lstobj	*new_obj(void *object, int type, float reflective)
{
	t_lstobj *objs;

if (!(objs = malloc(sizeof(t_lstobj))))
		print_errors(-6); //
	objs->obj = object;
	objs->type = type;
	objs->next = NULL;
	return (objs);
}

t_lstobj	*lstlast(t_lstobj *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
	{
		lst = lst->next;
	}
	return (lst);
}

int			lstadd_back(t_lstobj **lst, void *object, int type,
float reflective)
{
	t_lstobj *last;

	if (!object)
		return (-1);
	if (*lst == NULL)
	{
		*lst = new_obj(object, type, reflective);
		return (0);
	}
	last = lstlast(*lst);
	last->next = new_obj(object, type, reflective);
	return (0);
}
