/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mflor <mflor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/17 23:57:37 by mflor             #+#    #+#             */
/*   Updated: 2021/04/24 03:36:29 by mflor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_incicle(t_com *com)
{
	char	**commands;
	char	*line;
	int		t;

	get_next_line(&line, com);
	if (ft_forsplit(line, ';') > 0)
	{
		commands = ft_split(line, 10);
		t = -1;
		while (commands[++t])
		{
			commands[t] = ft_strtrim(commands[t], " ");
			ft_pipim(commands[t], com);
			free(commands[t]);
			commands[t] = NULL;
		}
	}
	if (line)
	{
		free(line);
		line = NULL;
	}
}

static void	ft_cominit(t_com *com)
{
	com->inited = 0;
	com->head = NULL;
	com->tail = NULL;
	com->buf = NULL;
	com->envp = NULL;
	com->args = NULL;
	com->env = NULL;
	com->thead2 = NULL;
	com->thead = NULL;
	com->tail = NULL;
	com->head = NULL;
	com->buf = NULL;
	com->redir = NULL;
}

void		sigint2(int num)
{
	(void)num;
}

void		sigquit2(int num)
{
	(void)num;
}

int			main(int argc, char **argv, char **envp)
{
	t_com	*com;

	com = malloc(sizeof(t_com));
	ft_lstadd_front_m(&g_mem, ft_lstnew_m1(com, 0));
	(void)argc;
	(void)argv;
	ft_cominit(com);
	ft_forenv(com, envp);
	if (com->fork == 2)
	{
		signal(SIGQUIT, sigquit);
		signal(SIGINT, sigint);
	}
	else if (com->fork > 2)
	{
		signal(SIGINT, sigint2);
		signal(SIGQUIT, sigquit2);
	}
	while (1)
	{
		ft_putstr_fd("minishell$", 1);
		ft_incicle(com);
	}
	return (0);
}
