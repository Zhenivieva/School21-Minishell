//
// Created by Murch Flor on 3/27/21.
//
#include "minishell.h"
# define MAXDIR 50

int		ft_pwd(void)
{
	char dir[MAXDIR];

	printf ("%s\n", getcwd(dir, MAXDIR));

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
