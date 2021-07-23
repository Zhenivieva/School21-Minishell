/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaryjan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 11:59:32 by mmaryjan          #+#    #+#             */
/*   Updated: 2021/04/24 11:59:37 by mmaryjan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_codeforexit(int status, t_com *com)
{
	if (status == 0)
		com->exit = 0;
	else if (status == 2)
		com->exit = 130;
	else if (status == 3)
		com->exit = 131;
	else if (status == 256)
		com->exit = 1;
	else
		com->exit = status >> 8;
}

void	ft_helpredir(t_com *c)
{
	while (c->redir)
	{
		if (c->redir->type == 1)
		{
			c->f = open(c->redir->content, O_RDONLY);
			c->f2 = dup2(c->f, 0);
		}
		else if (c->redir->type == 2)
		{
			c->f = open(c->redir->content, O_WRONLY | O_CREAT | O_TRUNC, 0777);
			c->f2 = dup2(c->f, 1);
		}
		else if (c->redir->type == 3)
		{
			c->f = open(c->redir->content, O_CREAT | O_APPEND | O_RDWR, 0644);
			c->f2 = dup2(c->f, 1);
		}
		close(c->f);
		if (c->f == -1)
		{
			dup2(c->def_fd1, 1);
			ft_error(8);
		}
		c->redir = c->redir->next;
	}
}

void	ft_helpfork(t_com *com)
{
	t_list	*temp;

	temp = com->redir;
	ft_helpredir(com);
	com->redir = temp;
	if (ft_builtin(com))
	{
		if (ft_slash(com->args[0]))
			ft_relabsbin(com);
		if (execve(com->args[0], com->args, com->envp) == -1)
			ft_error(6);
	}
	com->exit = 15;
	exit(com->exit);
}

int		ft_redir(t_com *com)
{
	int	wstatus;
	int pid;

	dup2(0, com->def_fd0);
	dup2(1, com->def_fd1);
	pid = fork();
	if (pid == -1)
		ft_error(7);
	if (pid == 0)
		ft_helpfork(com);
	else
	{
		wait(&wstatus);
		ft_codeforexit(wstatus, com);
	}
	return (0);
}
