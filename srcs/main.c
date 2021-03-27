

#include <stdio.h>
#include <unistd.h>
#include "minishell.h"
#include <string.h>
#include "get_next_line.h"
# define MAXDIR 50

int main(int argc, char **argv, char **envp)
{

	t_main_struct base;
	char *line;
	int fd;
	int i;
	char dir[MAXDIR];
	char **commands;
	int t;

	fd = 0;
	i = 1;
	getcwd(dir, MAXDIR);

	while (i > 0)
	{
		write(1, "success_minishell$", 18);
		i = get_next_line(fd, &line);
		ft_forsplit(line, ';');
		commands = ft_split(line, 10);
		t = -1;
		while (commands[++t])
		{
			commands[t] = ft_strtrim(commands[t], " ");
			printf("%d-%s\n", t, commands[t]);
			ft_pipim(commands[t], envp);
		}
//		parsing(line, copyenvp);
//		printf("%s\n", line);
		if (!(strncmp(line, "pwd", 4)))
		{
			getcwd(dir, MAXDIR);
			printf("%s\n", dir);
		}
	}
	t = -1;
	while (envp[++t])
	{
		printf("t-%s\n", envp[t]);
	}
	printf("Success minishell in three weeks!\n");
	return 0;
}

