//
// Created by Murch Flor on 3/27/21.
//
#include "minishell.h"

int		ft_pwd(void)
{
	char dir[50];

	printf ("%s\n", getcwd(dir, 50));

	return (0);

}

int		ft_echo(t_com *com)
{

}

int		ft_export(t_com *com, char **envp)
{

}

int		ft_unset(t_com *com, char **envp)
{

}

int		ft_cd(t_com *com, char **envp)
{

}

int		ft_env(t_com *com, char **envp)
{

}

int		ft_exit(char **envp)
{

}
