

#include <stdio.h>
#include <unistd.h>
#include "minishell.h"
#include <string.h>
//#include "get_next_line.h"
# define MAXDIR 50

int main(int argc, char **argv, char **envp)
{
	char *line;
	int i;
	t_com *com;
	char **commands;
	int t;

	i = 1;
	com = malloc(sizeof(t_com));
	(void)argc;
	(void)argv;

//	t_tlist *thead;
	com->inited = 0;
	com->head = NULL;
	com->tail = NULL;
	ft_forenv(com, envp);
	signal(SIGQUIT, sigquit);
	signal(SIGINT, sigint);
	while (i > 0)
	{
//		printf("minishell:");
//		write(1, "success_minishell$", 18);
		ft_putstr_fd("minishell$", 1);
//		thead = com->head;
		i = get_next_line(&line, com);
//		i = get_next_line1(1, &line);
//		printf("line in main %s\n", line);
//		com->head = thead;

		if (i == -1)
			ft_error(5);
		if (ft_forsplit(line, ';') > 0)
		{
			commands = ft_split(line, 10);
			t = -1;
			while (commands[++t])
			{
				commands[t] = ft_strtrim(commands[t], " ");
//			printf("%d-%s\n", t, commands[t]);
				ft_pipim(commands[t], com);
				free(commands[t]);
				commands[t] = NULL;
			}
		}
		if (line)
			free(line);
		line = NULL;
	}

	return 0;
}

