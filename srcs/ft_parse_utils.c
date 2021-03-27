//
// Created by Murch Flor on 3/27/21.
//
#include "minishell.h"

int ft_getdollar(char *dollar, t_com *com, int *b, int *a)
{
	int t;
	int c;
	int ret;

	t = -1;
	while (com->envp[++t])
		printf("dollar-%d-%s\n", t, com->envp[t]);
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
