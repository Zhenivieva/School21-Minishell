/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaryjan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 11:46:56 by mmaryjan          #+#    #+#             */
/*   Updated: 2021/01/15 11:48:15 by mmaryjan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_errors(int ernum, char *line)
{
	if (ernum == -1)
	{
		write(STDERR_FILENO, "minishell: ", 11);
		ft_putstr_fd(line, STDERR_FILENO);
		write(STDERR_FILENO, ": command not found", 19);
	}
	if (ernum == -6)
		write(STDERR_FILENO, "Error\nMalloc error", 18);

	//printf("minishell: %s: command not found", line); выводит не в поток ошибок
	/*
	//исправить описание ошибок
	ernum == -3 ? write(STDERR_FILENO, "Error\nThe second argument is invalid",
36) : 0;
	ernum == -4 ? write(STDERR_FILENO, "Error\nCouldn't open the file",
34) : 0;
	ernum == -6 ? write(STDERR_FILENO, "Error\nMalloc error", 18) : 0;
	ernum == -7 ? write(STDERR_FILENO, "Error\nCouldn't create file",
26) : 0;
	 */
	exit(ernum);
}