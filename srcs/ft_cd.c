//
// Created by Murch Flor on 4/11/21.
//
#include "minishell.h"

int		ft_cd(t_com *com)
{
	char pwd[300];
	com->oldpwd = getcwd(pwd, 300);
	printf("%s\n", com->oldpwd);


	if (com->args[1])
	{
		if ((chdir(com->args[1])) < 0)
		{
			ft_putstr_fd("minishell: ", 1);
			ft_putstr_fd(strerror(errno), 1);
			write(1, "\n", 1);
		}
//		else
//		{
//			while(com->env)
//		}
	}


	 return (0);

}
