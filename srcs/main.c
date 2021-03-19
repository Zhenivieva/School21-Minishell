

#include <stdio.h>
#include <unistd.h>
#include "minishell.h"
#include <string.h>
#include "get_next_line.h"
<<<<<<< HEAD
<<<<<<< HEAD
# define MAXDIR 300
=======
# define MAXDIR 50
>>>>>>> 005ac1499ffd0b4619093b44c2a7d243ef7b3dac
=======
# define MAXDIR 50
>>>>>>> 005ac1499ffd0b4619093b44c2a7d243ef7b3dac

int main(int argc, char **argv, char **envp)
{

	t_main_struct base;
	char *line;
	int fd;
	int i;
	char dir[MAXDIR];

	fd = 0;
	i = 1;
	getcwd(dir, MAXDIR);

	while (i > 0)
	{
		write(1, "success_minishell$", 18);
		i = get_next_line(fd, &line);
//		parsing(line, copyenvp);
//		printf("%s\n", line);
		if (!(strncmp(line, "pwd", 4)))
		{
			getcwd(dir, MAXDIR);
			printf("%s\n", dir);
		}
	}
	int t = -1;
	while (envp[++t])
	{
		printf("t-%s\n", envp[t]);
	}
	printf("Success minishell in three weeks!\n");
	return 0;
}

