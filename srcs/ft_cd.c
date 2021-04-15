//
// Created by Murch Flor on 4/11/21.
//
#include "minishell.h"

void    ft_copypwd(t_com *com)
{
    int t;
    char *temp;
    t_env *temp2;

    t = -1;
    while (com->envp[++t])
    {
        if (!(ft_strncmp(com->envp[t], "PWD", 3)))
        {
            temp = com->envp[t];
            com->envp[t] = ft_strjoin("PWD=", com->curpwd);
            free(temp);
        }
        if (!(ft_strncmp(com->envp[t], "OLDPWD", 6)))
        {
            temp = com->envp[t];
            com->envp[t] = ft_strjoin("OLDPWD=", com->oldpwd);
            free(temp);
        }
    }
    temp2 = com->env;
    while(com->env)
    {
        if (!(ft_strcmp(com->env->key, "PWD")))
        {
            temp = com->env->content;
            com->env->content = ft_strdup(com->curpwd);
            free(temp);
        }
        if (!(ft_strcmp(com->env->key, "OLDPWD")))
        {
            temp = com->env->content;
            com->env->content = ft_strdup(com->oldpwd);
            free(temp);
        }
        com->env = com->env->next;
    }
    com->env = temp2;
}

int		ft_cd(t_com *com)
{
	char pwd[300];
	int flag;
	t_env *temp;
//	char *temp;
//	com->oldpwd = getcwd(pwd, 300);
//	printf("%s\n", com->curpwd);

	flag = 0;
	if (!(com->args[1]))
	{
		temp = com->env;
		while (com->env)
		{
			if (!(ft_strcmp(com->env->key, "HOME")))
			{
				if (com->env->content)
					com->args[1] = com->env->content;
				else
					write(1, "HOME didn't set\n", 16);
				flag = 1;
			}
			com->env = com->env->next;
		}
		com->env = temp;
		if (!flag)
			write(1, "HOME didn't set\n", 16);
	}
	if ((chdir(com->args[1])) < 0)
	{
		ft_putstr_fd("minishell: ", 1);
		ft_putstr_fd(strerror(errno), 1);
		write(1, "\n", 1);
	}
	else
	{
		com->oldpwd = com->curpwd;
		com->curpwd = ft_strdup(getcwd(pwd, 300));
		ft_copypwd(com);

	}


		return (0);


	}