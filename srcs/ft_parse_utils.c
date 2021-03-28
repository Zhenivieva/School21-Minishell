//
// Created by Murch Flor on 3/27/21.
//
#include "minishell.h"

int ft_getdollar(char *dollar, t_com *com, int *b, int *a)
{
	int t;
	int c;
	int ret;


	c = 0;
	while (dollar[c] != '\0' && dollar[c] != '$'
	&& dollar[c] != '\\' && dollar[c] != '\''
	&& dollar[c] != '"' && dollar[c] != ' ')
	{
			 c++;
	}
	ret = c;
//добавить реаллок com->args[*a]
	t = -1;
	while (com->envp[++t])
		if (!(ft_strncmp(com->envp[t], dollar, c)))
		{
			c++;
			while (com->envp[t][c])
				com->args[*a][(*b)++] = com->envp[t][c++];
		}
	return (ret + 1);
}

char *ft_getpath(t_com *com)
{
	char *path;
	int t;
	int c;
	int a;
	int count;

	a = 0;
	c = 4;
	count = 0;
	t = -1;
	while (com->envp[++t])
		if (!(ft_strncmp(com->envp[t], "PATH", 4)))
		{
			while (com->envp[t][++c])
				count++;
			c = 5;
			path = malloc(count + 1);
			while (com->envp[t][c])
				path[a++] = com->envp[t][c++];
		}
	return (path);
}

void 	ft_relabsbin(t_com *com)
{
	char **paths;
//	char *path;
	int t;
	int fd;
	char *temp;
	char *temp2;

	paths = ft_split(ft_getpath(com), ':');
	t = -1;
	while (paths[++t])
	{
		temp = ft_strjoin(paths[t], "/");
		temp2 = ft_strjoin(temp, com->args[0]);
		free (temp);
		if (open(temp2, O_RDONLY) > 0)
		{
			temp = com->args[0];
			com->args[0] = temp2;
			free(temp);
		}
	}
}