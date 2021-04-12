//
// Created by Murch Flor on 4/11/21.
//
#include "minishell.h"

void    ft_copypwd(t_com *com)
{
    int t;
    char *temp;
    char *temp2;

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
	char *temp;
//	com->oldpwd = getcwd(pwd, 300);
	printf("%s\n", com->curpwd);


	if (com->args[1])
	{
		if ((chdir(com->args[1])) < 0)
		{
			ft_putstr_fd("minishell: ", 1);
			ft_putstr_fd(strerror(errno), 1);
			write(1, "\n", 1);
		}
		else
        {
//		    temp = com->oldpwd;
		    com->oldpwd = com->curpwd;
//		    temp = com->curpwd;
		    com->curpwd = ft_strdup(getcwd(pwd, 300));
//		    free(temp);
		    ft_copypwd(com);
            printf("curpwd:%s\n", com->curpwd);
            printf("oldpwd:%s\n", com->oldpwd);
        }
//		else
//		{
//			while(com->env)
//		}
	}


	 return (0);

}
