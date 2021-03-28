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
	if (n == 5)
		printf("FD with gnl problem\n");
	if (n == 6)
		printf("Execve problem\n");
	if (n == -6)
		printf("Unknown program\n");
	if (n > 0)
		exit(n);
	return (n);
}

int	ft_forsplit(char *line, char k)
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
					return(ft_error(-1));
			}
		}
		if (line[t] == '\'')
		{
			while (line[++t] != '\'')
				if (line[t] == '\0')
					return (ft_error(-1));
		}
		if (line[t] == '\\')
			t = t + 2;
		if (line[t] == k)
			line[t] = 10;
	}
	return (1);
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

void double_quotes(char *pipecom, t_com *com, t_indexes *inds)
{
	if (pipecom[inds->k] == '"')
	{
		inds->k++;
		while (pipecom[inds->k] != '"') {
			if (pipecom[inds->k] == '\\' && (pipecom[inds->k + 1] == '$'
										  || pipecom[inds->k + 1] == '"' || pipecom[inds->k + 1] == '\\'))
				inds->k++;
			if (pipecom[inds->k] == '$')
			{
				inds->k = inds->k +
					ft_getdollar(pipecom + inds->k + 1, com, &(inds->b), &(inds->a));
				continue;
			}
			if (pipecom[inds->k] != '$')
				com->args[inds->a][inds->b++] = pipecom[inds->k++];
//						if (pipecom[t][k] == '"')
//							k++;
		}
		inds->k++;
//					com->args[a][b++] = pipecom[t][k++];
	}
}



void ft_parsecom(char *pipecom, t_com *com)
{
	t_indexes inds;

	inds.k = -1;
	inds.a = 0;
	while (pipecom[++inds.k])
	{
		com->args = malloc(sizeof(char *) * (ft_numargs(pipecom) + 2));
		if (!com->args)
			ft_error(-4);
		inds.k = 0;
		while (pipecom[inds.k])
		{
			inds.b = 0;
			while (pipecom[inds.k] == ' ')
				inds.k++;
			com->args[inds.a] = malloc(ft_numcommand(pipecom + inds.k) + 301);
			if (com->args == NULL)
				ft_error(-3);
			parse_word(pipecom, com, &inds);
			com->args[inds.a][inds.b] = '\0';
//			printf("com->argc[%d]-%s\n", a, com->args[a]);
			inds.a++;
		}
		com->args[inds.a] = NULL;
	}
}

int ft_builtin(t_com *com)
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

int ft_forexecve(t_com *com)
{
	pid_t pid;

	if (ft_slash(com->args[0]))
	{
		if (ft_relabsbin(com))
		{
			pid = fork();
			if (pid == 0)
				if (execve(com->args[0], com->args, com->envp) == -1)
					ft_error(6);
			waitpid(pid, NULL, 0);
		}
		else
			ft_error(-6);
	}
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

void	ft_pipe(t_com *com, char **pipecom)
{
	int	fd[2];
//	int fd2[2];
	int	cpid1;
	int	cpid2, cpid3;

	dup2(com->def_fd0, 0);
	dup2(com->def_fd1, 1);

//	dup2(fd2[0], fd[0]);
//	dup2(fd2[1], fd[1]);
		if (pipe(fd) == -1)
			ft_error(3);

		cpid1 = fork();
		if (cpid1 == -1) {
			perror("fork");   //заменить функцию
			exit(1);
		}
		if (cpid1 == 0) {
			dup2(fd[1], STDOUT_FILENO);
			close(fd[0]);
			close(fd[1]);
			ft_parsecom(pipecom[0], com);
			if (ft_builtin(com))
				(ft_forexecve(com));
			exit(1);
		}
		cpid2 = fork();
		if (cpid2 == -1) {
			perror("fork");
		exit(1);   //почему приходится это делать?????
		}
		if (cpid2 == 0) {
			dup2(fd[0], STDIN_FILENO);
			close(fd[0]);
			close(fd[1]);
			ft_parsecom(pipecom[1], com);
			if (ft_builtin(com))
				(ft_forexecve(com));
		exit(2);  //и тут, непонятно, поччему надо писать эксит????
	}
/* проба с 3 форком*/
//	cpid3 = fork();
//	if (cpid3 == -1)
//	{
//		perror("fork");
//		exit(1);   //почему приходится это делать?????
//	}
//	if (cpid3 == 0)
//	{
//		dup2(fd[0], STDIN_FILENO);
//		close(fd[0]);
//		close(fd[1]);
//		ft_parsecom(pipecom[2], com);
//		if (ft_builtin(com))
//			(ft_forexecve(com));
//		exit(3);  //и тут, непонятно, поччему надо писать эксит????
//	}
	/*проба с третьим формком*/
	close(fd[0]);
	close(fd[1]);
	waitpid(cpid1, NULL, 0);
	waitpid(cpid2, NULL, 0);
//	waitpid(cpid3, NULL, 0);


	dup2(0, com->def_fd0);
	dup2(1, com->def_fd1);
	//dup2(fd[0], fd2[0]);
	//	dup2(fd[1], fd2[1]);


}

void ft_pipim(char *command, char **envp)
{
	t_com	*com;
	char	**pipecom;
	int		t;

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
	if (!(pipecom[1]))
	{
		ft_parsecom(pipecom[0], com);
		if (ft_builtin(com))
			(ft_forexecve(com));
	}
	else
		ft_pipe(com, pipecom);
}