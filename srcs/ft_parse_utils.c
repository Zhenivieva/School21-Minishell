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

int 	ft_relabsbin(t_com *com)
{
	char **paths;
//	char *path;
	int t;
	int flag;
	char *temp;
	char *temp2;

	flag = 0;
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
			flag = 1;
		}
	}
	if (flag)
		return (1);
	return (0);
}

void parse_word(char *pipecom, t_com *com, t_indexes *inds)
{
	while (pipecom[inds->k] != ' ' && pipecom[inds->k] != '\0')
	{
		double_quotes(pipecom, com, inds);
		if (pipecom[inds->k] == '\'')
		{
			while (pipecom[++inds->k] != '\'')
				com->args[inds->a][inds->b++] = pipecom[inds->k];
			inds->k++;
		}
		else if (pipecom[inds->k] == '$')
		{
			inds->k = inds->k + ft_getdollar(pipecom + inds->k + 1, com, &inds->b, &inds->a); //&inds
			continue;
		}
		else if (pipecom[inds->k] != '$')
		{
			if (pipecom[inds->k] == '<')
			{
				com->less[inds->a + 1] = 1;
				inds->k++;
				break;
			}
			if (pipecom[inds->k] == '>' && pipecom[inds->k + 1] == '>')
			{
				com->append[inds->a + 1] = 1;
				inds->k++;
				break;
			}
			if (pipecom[inds->k] == '>' && pipecom[inds->k + 1] != '>')
			{
				com->great[inds->a + 1] = 1;
				com->konecg = inds->a + 1;
				inds->k++;
				break;
			}
			com->args[inds->a][inds->b++] = pipecom[inds->k++];
		}
	}
}