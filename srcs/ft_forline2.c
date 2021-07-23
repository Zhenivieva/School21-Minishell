/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_forline2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaryjan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 03:39:32 by mmaryjan          #+#    #+#             */
/*   Updated: 2021/04/24 03:39:59 by mmaryjan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_error(int n)
{
	if (n == -1)
		printf("Ne zakryty kavicki\n");
	if (n == -2)
		printf("Malloc problem2222\n");
	if (n == -3)
		printf("Malloc problem3333\n");
	if (n == 4)
		printf("Malloc problem4444\n");
	if (n == 5)
		printf("FD with gnl problem\n");
	if (n == 6)
		printf("minishell: unknown program\n");
	if (n == -6)
		printf("minishell: syntax error near unexpected token\n");
	if (n == -7)
		printf("minishell: syntax error near unexpected token\n");
	if (n == -8)
		printf("minishell: syntax error near unexpected token\n");
	if (n == 7)
		printf("Fork returned -1\n");
	if (n == 8)
		printf("minishell: syntax error\n");
	if (n > 0)
		exit(n);
	return (n);
}

int		ft_builtin(t_com *com)
{
	if (!(ft_strcmp(com->args[0], "pwd")))
		return (ft_pwd());
	if (!(ft_strcmp(com->args[0], "echo")))
		return (ft_echo(com));
	if (!(ft_strcmp(com->args[0], "export")))
		return (ft_export(com));
	if (!(ft_strcmp(com->args[0], "unset")))
		return (ft_unset(com));
	if (!(ft_strncmp(com->args[0], "cd", 3)))
		return (ft_cd(com));
	if (!(ft_strncmp(com->args[0], "env", 4)))
		return (ft_env(com));
	if (!(ft_strcmp(com->args[0], "exit")))
		return (ft_exit(com));
	return (1);
}

int		ft_slash(char *comand)
{
	int	t;

	t = -1;
	while (comand[++t])
	{
		if (comand[t] == '.')
			return (0);
		else if (comand[t] == '/')
			return (0);
	}
	return (1);
}

int		ft_forexecve(t_com *com)
{
	pid_t	pid;
	int		wstatus;

	if (com->konecg == 0)
	{
		if (ft_builtin(com))
		{
			if (ft_slash(com->args[0]))
				ft_relabsbin(com);
			pid = fork();
			if (pid == 0)
			{
				if (execve(com->args[0], com->args, com->envp) == -1)
					ft_errno(com->args[0], -1, com);
			}
			waitpid(pid, &wstatus, 0);
			ft_codeforexit(wstatus, com);
		}
	}
	else
		return (ft_redir(com));
	return (0);
}

void	ft_pipim(char *command, t_com *com)
{
	char	**pipecom;

	com->konecg = 0;
	if (ft_forsplit(command, '|') > 0)
	{
		pipecom = ft_split(command, 10);
		com->npipes = -1;
		while (pipecom[++com->npipes])
		{
			pipecom[com->npipes] = ft_strtrim(pipecom[com->npipes], " ");
		}
		if (!(pipecom[1]))
		{
			ft_parsecom(pipecom[0], com);
			ft_forexecve(com);
		}
		else
			ft_pipes(com, pipecom);
	}
}
