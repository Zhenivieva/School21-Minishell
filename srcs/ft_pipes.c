/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipes.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaryjan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 12:03:13 by mmaryjan          #+#    #+#             */
/*   Updated: 2021/04/24 12:03:16 by mmaryjan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_closefd(int npipes, int pipes[npipes][2])
{
	int j;

	j = -1;
	while (++j < npipes)
	{
		close(pipes[j][0]);
		close(pipes[j][1]);
	}
}

void	ft_helppipe1(t_com *com, int pipes[com->npipes][2])
{
	int i;

	dup2(0, com->def_fd0);
	dup2(1, com->def_fd1);
	i = -1;
	while (++i < com->npipes)
	{
		if (pipe(pipes[i]) == -1)
		{
			printf("Erorr with creating pipe\n");
			exit(-5);
		}
	}
}

void	ft_helppipe(t_com *com, int pipes[com->npipes][2], char **pcom, int i)
{
	if (i == 0)
		dup2(pipes[i][1], 1);
	else if ((i < com->npipes - 1) && (i > 0))
	{
		dup2(pipes[i - 1][0], 0);
		dup2(pipes[i][1], 1);
	}
	else if (i == com->npipes - 1)
		dup2(pipes[i - 1][0], 0);
	ft_closefd(com->npipes, pipes);
	ft_parsecom(pcom[i], com);
	(ft_forexecve(com));
	com->exit = 11;
	exit(com->exit);
}

void	ft_pipes(t_com *com, char **pipecom)
{
	int	i;
	int	wstatus;
	int	pids[com->npipes];
	int	pipes[com->npipes][2];

	ft_helppipe1(com, pipes);
	i = -1;
	while (++i < com->npipes)
	{
		pids[i] = fork();
		if (pids[i] == -1)
			ft_error(7);
		if (pids[i] == 0)
			ft_helppipe(com, pipes, pipecom, i);
	}
	ft_closefd(com->npipes, pipes);
	i = -1;
	while (++i < com->npipes)
		waitpid(pids[i], &wstatus, 0);
	ft_codeforexit(wstatus, com);
	dup2(com->def_fd0, 0);
	dup2(com->def_fd1, 1);
}
