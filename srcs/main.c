

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



	ft_forenv(com, envp);
	while (i > 0)
	{
//		printf("minishell:");
//		write(1, "success_minishell$", 18);
		ft_putstr_fd("minishell$", 1);
//		i = get_next_line(fd, &line);
		i = get_next_line(&line);
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
		free(line);
		line = NULL;
	}

	return 0;
}

