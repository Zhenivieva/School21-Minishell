#include "minishell.h"

int main(int argc, char **argv, char **envp)
{

	t_main_struct	base;
	char			*copyenvp;

	copyenvp = *envp;

	parse_main(&copyenvp);
	/*
	i = 1;
	getcwd(dir, MAXDIR);
	while (i > 0)
	{
		write(1, "success_minishell$", 18);
		i = get_next_line(fd, &line);
		if (!(ft_strncmp(line, "pwd", 4)))
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
	 */
	printf("Success minishell in three weeks!\n");

	return 0;
}
/*
// версия 19.03.2021
int main(int argc, char **argv, char **envp)
{

	t_main_struct	base;
	char			*line;
	int				fd;
	int				i;
	char			dir[MAXDIR];

	fd = 0;
	i = 1;
	getcwd(dir, MAXDIR);

	while (i > 0)
	{
		write(1, "success_minishell$ ", 19);
		i = get_next_line(fd, &line);
//		parsing(line, copyenvp);
//		printf("%s\n", line);
		if (!(ft_strncmp(line, "pwd", 4)))
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
*/

