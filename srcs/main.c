/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mflor <mflor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/17 23:57:37 by mflor             #+#    #+#             */
/*   Updated: 2021/04/18 00:01:48 by mflor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void ft_cominit(t_com *com)
{
	com->inited = 0;
	com->head = NULL;
	com->tail = NULL;
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	int		i;
	t_com	*com;
	char	**commands;
	int		t;

	i = 1;
	com = malloc(sizeof(t_com));
	ft_lstadd_front_m(&g_mem, ft_lstnew(com, 0));
	(void)argc;
	(void)argv;
	ft_cominit(com);
	ft_forenv(com, envp);
	if (com->fork == 2)
	{
		signal(SIGQUIT, sigquit);
		signal(SIGINT, sigint);
	}
	while (i > 0)
	{
		ft_putstr_fd("minishell$", 1);
		i = get_next_line(&line, com);
		if (i == -1)
			ft_error(5);
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
		line = NULL;
	}
	return (0);
}
