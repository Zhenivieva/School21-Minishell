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
	if (n == -5)
		printf("FD with gnl problem\n");
	if (n == -6)
		printf("Execve oblem\n");
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
			{
				if (line[t] == '\\')
					t = t + 2;
				if (line[t] == '\0')
					ft_error(-1);
			}
		}
		if (line[t] == '\'')
		{
			while (line[++t] != '\'')
				if (line[t] == '\0')
					ft_error(-1);
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
//void double_quotes(char **pipecom, t_com *com)
//{
//
//}

void ft_parsecom(char **pipecom, t_com *com)
{
	int t;
	int k;
	int a;
	int b;

	t = -1;
	a = 0;
	while (pipecom[++t])
	{
		com->args = malloc(sizeof(char *) * (ft_numargs(pipecom[t]) + 2));
		if (!com->args)
			ft_error(-4);
		k = 0;
		while (pipecom[t][k])
		{
			b = 0;
			while (pipecom[t][k] == ' ')
				k++;
			com->args[a] = malloc(ft_numcommand(pipecom[t] + k) + 301);
			if (com->args == NULL)
				ft_error(-3);
			while (pipecom[t][k] != ' ' && pipecom[t][k] != '\0')
			{
				if (pipecom[t][k] == '"')
				{
					k++;
					while (pipecom[t][k] != '"') {
						if (pipecom[t][k] == '\\' && (pipecom[t][k + 1] == '$'
													  || pipecom[t][k + 1] == '"' || pipecom[t][k + 1] == '\\'))
							k++;
						if (pipecom[t][k] == '$')
						{
							k = k +
								ft_getdollar(pipecom[t] + k + 1, com, &b, &a);
							continue;
						}
						if (pipecom[t][k] != '$')
							com->args[a][b++] = pipecom[t][k++];
//						if (pipecom[t][k] == '"')
//							k++;
					}
					k++;
//					com->args[a][b++] = pipecom[t][k++];
				}
				if (pipecom[t][k] == '\'')
				{
					while (pipecom[t][++k] != '\'')
						com->args[a][b++] = pipecom[t][k];
					k++;
				}
				else if (pipecom[t][k] == '$')
				{
					k = k +
						ft_getdollar(pipecom[t] + k + 1, com, &b, &a);
					continue;
				}
				else if (pipecom[t][k] != '$')
					com->args[a][b++] = pipecom[t][k++];
			}
			com->args[a][b] = '\0';
//			printf("com->argc[%d]-%s\n", a, com->args[a]);
			a++;
		}
		com->args[a] = NULL;
	}
}

int ft_builtin(t_com *com, char **envp)
{
	if (!(ft_strncmp(com->args[0], "pwd", 4)))
		return (ft_pwd());
//	if (!(ft_strncmp(com->args[0], "echo", 5)))
//		return (ft_echo(com));
//	if (!(ft_strncmp(com->args[0], "export", 7)))
//		return (ft_export(com, envp));
//	if (!(ft_strncmp(com->args[0], "unset", 6)))
//		return (ft_unset(com, envp));
//	if (!(ft_strncmp(com->args[0], "cd", 3)))
//		return (ft_cd(com, envp));
//	if (!(ft_strncmp(com->args[0], "env", 4)))
//		return (ft_env(com, envp));
//	if (!(ft_strncmp(com->args[0], "exit", 5)))
//		return (ft_exit(envp));
	return (1);
}

int ft_slash(char *comand)
{
	int t;

	t = -1;
	while (comand[++t])
	{
		if (comand[t] == '.')
			return (0);
		else if (comand[t] == '/')
			return (0);
	}
	return (1);
}

int ft_forexecve(t_com *com, char **envp)
{
	int pid;

	if (ft_slash(com->args[0]))
		ft_relabsbin(com);
//		com->komand = ft_strjoin("/bin/", com->komand); //вместо /bin/ функция по поиску этой функции
	pid = fork();
//	printf("pid=%d\n", pid);
	if (pid != 0)
		wait(pid);
	if (pid == 0)
		if (execve(com->args[0], com->args, envp) == -1)
			ft_error(-6);
}

int		ft_kolenvp(char **envp)
{
	int t;
	int c;

	t = -1;
	c = 0;
	while (envp[++t])
		c++;
//	printf("kolichestvo-%d\n", c);
	return (c);
}

void ft_pipim(char *command, char **envp)
{
	t_com *com;
	char **pipecom;
	int t;

	com = malloc(sizeof(t_com));
	com->envp = malloc(sizeof (char *) * (ft_kolenvp(envp) + 1));
	if (!(com && com->envp))
		ft_error(-2);
	t = -1;
	while (envp[++t])
		com->envp[t] = ft_strdup(envp[t]);
	com->envp[t] = NULL;

	ft_forsplit(command, '|');
	pipecom = ft_split(command, 10);
	t = -1;
	while(pipecom[++t])
		pipecom[t] = ft_strtrim(pipecom[t], " ");
	ft_parsecom(pipecom, com);
	if (ft_builtin(com, envp))
		(ft_forexecve(com, envp));
}