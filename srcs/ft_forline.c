#include "minishell.h"

int ft_error(int n)
{
	if (n == -1)
		printf("Ne zakryty kavicki\n");
	if (n == -2)
		printf("Malloc problem2222\n");
	if (n == -3)
		printf("Malloc problem3333\n");
	if (n == -4)
		printf("Malloc problem4444\n");
	exit(n);
}

void	ft_forsplit(char *line, char k)
{
	int t;

	t = -1;
	while (line[++t])
	{
		if (line[t] == '"')
		{
			while (line[++t] != '"')
				if (line[t] == '\0')
					ft_error(-1);
			t++;
		}
		if (line[t] == '\'')
		{
			while (line[++t] != '\'')
				if (line[t] == '\0')
					ft_error(-1);
			t++;
		}
		if (line[t] == '\\')
			t = t + 2;
		if (line[t] == k)
			line[t] = 10;
	}
}

int		ft_numcommand(char *command)
{
	int t;
	int c;

	c = 0;
	t = -1;
	while (command[++t] != ' ' && command[t] != '\0')
		c++;
	return (c);
}

int 	ft_numargs(char *command)
{
	int t;
	int c;

	c = 0;
	t = -1;
	while (command[++t])
	{
		if (command[t] == ' ')
		{
			while (command[t] == ' ')
				t++;
			c++;
		}
	}
	return (c);
}

void ft_parsecom(char **pipecom, t_com *com)
{
	int t;
	int k;
	int a;
	int b;

	t = -1;
	a = 0;
	com = malloc(sizeof(t_com));
	if (!(com))
		ft_error(-2);
	while (pipecom[++t])
	{
		k = 0;
		b = 0;
		com->args = malloc(sizeof(char *) * (ft_numargs(pipecom[t]) + 1));
		com->komand = malloc(ft_numcommand(pipecom[t]) + 1);
		if (!(com->args  && com->komand))
			ft_error(-4);
		while (pipecom[t][k] != ' ' && pipecom[t][k] != '\0')
			com->komand[b++] = pipecom[t][k++];
		com->komand[b] = '\0';
		printf("komand-%s\n", com->komand);
		while (pipecom[t][k])
		{
			b = 0;
			while (pipecom[t][k] == ' ')
				k++;
			com->args[a] = malloc(ft_numcommand(pipecom[t] + k) + 1);
			if (com->args == NULL)
				ft_error(-3);
			while (pipecom[t][k] != ' ' && pipecom[t][k] != '\0')
				com->args[a][b++] = pipecom[t][k++];
			com->args[a][b] = '\0';
			printf("%d-%s\n", a, com->args[a]);
			a++;
		}

	}
}

void ft_pipim(char *command, char **envp)
{
	t_com com;
	char **pipecom;
	int t;

	t = -1;
	ft_forsplit(command, '|');
	pipecom = ft_split(command, 10);
	while(pipecom[++t])
		pipecom[t] = ft_strtrim(pipecom[t], " ");
	ft_parsecom(pipecom, &com);
}