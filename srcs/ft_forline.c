#include "minishell.h"

int ft_error(int n)
{
	if (n == -1)
		printf("Ne zakryty kavicki\n");
	if (n == -2)
		printf("Malloc problem2222\n");
	if (n == -3)
		printf("Malloc problem3333\n");
	if (n == 4)
		printf("Malloc problem4444\n");
	if (n == 5)
		printf("FD with gnl problem\n");
	if (n == 6)
		printf("Execve problem\n");
	if (n == -6)
		printf("Unknown program\n");
	if (n == 7)
		printf("Fork returned -1\n");
	if (n == 8)
		printf("Ne smog otkrity fail, sorry\n");
	if (n > 0)
		exit(n);
	return (n);
}

int	ft_forsplit(char *line, char k)
{
	int t;

	if (line == NULL)
		return (0);
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
	if (!command)
		return (0);
	while (command[++t] != '\0' && command[t] != ' ')
		c++;
	return (c);
}

int 	ft_numargs(char *command)
{
	int t;
	int c;

	c = 0;
	t = -1;
	if (!command)
		return (0);
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
		while (pipecom[inds->k] != '"')
		{
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


void ft_forenv(t_com *com, char **envp)
{
	int t;
	char **envstring; //НУЖНО!!!
//	t_env *temp;
	com->env = NULL;
//	com->env = malloc(sizeof(t_env));
	t = -1;
//	temp = com->env;

//	while(envp[++t])
//	{
//		printf("%s\n", envp[t]);
//	}

t = -1;
	while(envp[++t])
	{
		envstring = ft_split(envp[t], '=');
//		printf("-----------------------------------------\n");
//		printf("%s\n", envstring[0]);
//		printf("%s\n", envstring[1]);
//		printf("-----------------------------------------\n");
//		ft_lstadd_back1(&com->env, ft_lstnew1(envstring[0], envstring[1]));

		ft_putsorted(&com->env, ft_lstnew1(envstring[0], envstring[1]));
	}
//	printf("%s\n",com->env->key);
//	while (com->env)
//	{
//		printf("key=%s\n", com->env->key);
//		com->env = com->env->next;
//	}
	ft_shlvlinc(com);
//	com->env = temp;
//	com->envp = malloc(sizeof (char *) * (ft_kolenvp(envp) + 1));
//	if (!(com && com->envp))
//		ft_error(-2);
//	t = -1;
//	while (envp[++t])
//		com->envp[t] = ft_strdup(envp[t]);
//	com->envp[t] = NULL;



//	while (com->env)
//	{
//		write(1, "declare -x ", 11);
//		ft_putstr_fd(com->env->key, 1);
//		if (com->env->content)
//		{
//			write(1, "=\"", 2);
//			ft_putstr_fd(com->env->content, 1);
//			write(1, "\"", 1);
//		}
//		write(1, "\n", 1);
//		com->env = com->env->next;
//	}
//	com->env = temp;
}

void ft_parsecom(char *pipecom, t_com *com)
{
	t_indexes inds;
//	t_list *ret;
	com->file = malloc(sizeof(char *) * 10);
//	com->redir = malloc(sizeof(t_list *) * (300));
	inds.k = -1;
	inds.a = 0;

	int t;
//	while (pipecom[++inds.k])
//	{
		com->args = malloc(sizeof(char *) * (ft_numargs(pipecom) + 2));
		if (!com->args)
			ft_error(4);
		inds.k = 0;
		while (pipecom[inds.k])
		{
			inds.b = 0;
			t = 0;
			while (pipecom[inds.k] == ' ' || pipecom[inds.k] == '>' || pipecom[inds.k] == '<')
			{
				if (pipecom[inds.k] == '>' && pipecom[inds.k + 1] != '>')
				{
					inds.k++;
					while(pipecom[inds.k] == ' ')
						inds.k++;
					com->less[inds.a] = 1;
					com->konecg = 1;
//					com->file[t++] = (ft_forcontent(pipecom + inds.k, &inds.k));
					ft_lstadd_back(&com->redir, ft_lstnew(ft_forcontent(pipecom + inds.k, &inds.k), 2));
//					com->redir = ret;
					com->konecg++;
				}
				while (pipecom[inds.k] == '<')
				{
					inds.k++;
					while(pipecom[inds.k] == ' ')
						inds.k++;
					com->less[inds.a] = 2;
					com->konecg++;
//					com->file[t++] = (ft_forcontent(pipecom + inds.k, &inds.k));
					ft_lstadd_back(&com->redir, ft_lstnew(ft_forcontent(pipecom + inds.k, &inds.k), 1));
				}
				if (pipecom[inds.k] == '>' && pipecom[inds.k + 1] == '>')
				{
					inds.k = inds.k + 2;
					while(pipecom[inds.k] == ' ')
						inds.k++;
					com->less[inds.a] = 3;
					com->konecg++;
//					com->file[t++] = ft_strdup(ft_forcontent(pipecom + inds.k, &inds.k));
					ft_lstadd_back(&com->redir, ft_lstnew(ft_forcontent(pipecom + inds.k, &inds.k), 3));
//					com->redir = ft_lstnew(ft_forcontent(pipecom + inds.k, &inds.k));
				}
				if ((pipecom[inds.k] != '<') && (pipecom[inds.k] != '>'))
					inds.k++;
			}
			com->args[inds.a] = malloc(ft_numcommand(pipecom + inds.k) + 1000);
			if (com->args[inds.a] == NULL)
				ft_error(-3);
			parse_word(pipecom, com, &inds, &t);
			com->args[inds.a][inds.b] = '\0';
//			printf("com->argc[%d]-%s\n", a, com->args[a]);
			if (inds.b > 0)
				inds.a++;
		}
		com->args[inds.a] = NULL;
//	}

}

void ft_shlvlinc(t_com *com)
{
	t_env *temp;
	int temp2;
	char *temps;
	char temp3[300];
	temp = com->env;

	while(com->env)
	{
		if (!(ft_strcmp(com->env->key, "SHLVL")))
		{
			temp2 = ft_atoi(com->env->content);
			temp2++;
			temps = com->env->content;
			com->env->content = ft_itoa(temp2);
			free(temps);
			temps = NULL;
		}
		if (!(ft_strcmp(com->env->key, "OLDPWD")))
		{
			com->env->content = NULL;
			com->oldpwd = com->env->content;
		}
		if (!(ft_strcmp(com->env->key, "PWD")))
		{
            temps = com->env->content;
			com->env->content = ft_strdup(getcwd(temp3, 300));
            free(temps);
            temps = NULL;
            com->curpwd = com->env->content;
		}
		com->env = com->env->next;
	}
	com->env = temp;
	ft_copyenvp(com);
}


int ft_builtin(t_com *com)
{
	if (!(ft_strcmp(com->args[0], "pwd")))
		return (ft_pwd());
	if (!(ft_strcmp(com->args[0], "echo")))
		return (ft_echo(com));
	if (!(ft_strcmp(com->args[0], "export")))
		return (ft_export(com));
	if (!(ft_strcmp(com->args[0], "unset")))
		return (ft_unset(com));
	if (!(ft_strncmp(com->args[0], "cd", 3)))
		return (ft_cd(com));
	if (!(ft_strncmp(com->args[0], "env", 4)))
		return (ft_env(com));
	if (!(ft_strcmp(com->args[0], "exit")))
		return (ft_exit(com));
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
	int wstatus;

//	int t = -1;

//	while (com->args[++t])
//	{
//		printf("%d-%s\n", t, com->args[t]);
//	}
//	printf("com->konecg=%d\n", com->konecg);
//	if  (com->redir) {
//		printf("before cicle redir-content:%s\n", (char *) com->redir->content);
//		while (com->redir) {
//		    printf("type:%d\n", com->redir->type);
//			printf("redir-content:%s\n", (char *) com->redir->content);
//			com->redir = com->redir->next;
//		}
//	}

//	g_p[0] = 0;
	ft_forcat(com->args);
	if (com->konecg == 0)
	{

        if (ft_builtin(com))
        {
            if (ft_slash(com->args[0]))
            {
                if (!(ft_relabsbin(com)))
                {
                    ft_error(-6);
                }
            }
            pid = fork();
            if (pid == 0)
			{
            	if (execve(com->args[0], com->args, com->envp) == -1)
					ft_error(6);
			}
            waitpid(pid, &wstatus, 0);
            ft_codeforexit(wstatus, com);
        }
	}
	else
		ft_redir(com);
	return (0);
}

void ft_pipim(char *command, t_com *com)
{
	char	**pipecom;
	int		t;

	com->konecg = 0;
	ft_forsplit(command, '|');
	pipecom = ft_split(command, 10);
	t = -1;
	while(pipecom[++t])
	{
		pipecom[t] = ft_strtrim(pipecom[t], " ");
	}
	if (!(pipecom[1]))
	{
		ft_parsecom(pipecom[0], com);
		ft_forexecve(com);
	}
	else
		ft_pipes(com, pipecom, t);
}