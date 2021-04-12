//
// Created by Murch Flor on 3/27/21.
//
#include "minishell.h"

int		ft_pwd(void)
{
	char dir[300];

	printf ("%s\n", getcwd(dir, 300)); //putstr(getcwd(...))
	return (0);
}

int check_nflag(char *word)
{
	int nflag;
	int i;

	nflag = 0;
	if (!ft_strncmp(word, "-n", 3))
		nflag = 1;
	else if (!ft_strncmp(word, "-n", 2))
	{
		i = 1;
		nflag = 1;
		while (word[++i])
		{
			if (word[i] == 'n')
				continue;
			else
			{
				nflag = 0;
				break;
			}
		}
	}
	return (nflag);
}

int		ft_echo(t_com *com)
{
	int nflag;
	int a;

	a = 1;
	nflag = 0;
	if (com->args[a])
	{
        nflag = check_nflag(com->args[a]);
        while (check_nflag(com->args[a]))
            a++;
        while (com->args[a])
        {
            write(1, com->args[a], ft_strlen(com->args[a]));
            if (com->args[a + 1])
                write(1, " ", 1);
            a++;
        }
    }
	if (!nflag)
		write (1, "\n", 1);
	return (0);
}


//int		ft_cd(t_com *com)
//{
//
//}
//
//int		ft_env(t_com *com)
//{
//
//}

int	ft_proverkadigit(char *s)
{
	int t;
	int min;

	t = -1;
	while (s[++t])
	{
		if (s[t] == '-')
		{
			t++;
			min = 1;
		}
		if (!('0' <= s[t] && s[t] <= '9'))
		{
			printf("exit\n");
			printf("minishell: exit: %s:numeric argument required\n", s);
			exit(255);
		}
	}
	return (1);
}

int		ft_exit(t_com *com)
{
	int res;

	if (com->args[1])
	{
		if (ft_proverkadigit(com->args[1]))
		{
			if (com->args[2])
			{
				printf("exit\n");
				printf("minishell: exit: too many arguments\n");
				com->exit = 1;
				printf("com->exit in ft_exit:%d\n", com->exit);
				exit(com->exit);
			}
			else
			{
				printf("exit\n");
				res = ft_atoi(com->args[1]);
				com->exit = (res >= 0 ? res : 256 + res);
				printf("com->exit in ft_exit:%d\n", com->exit);
				exit(com->exit);
			}
		}
	}
	com->exit = 0;
	printf("com->exit in ft_exit:%d\n", com->exit);
	exit(com->exit);
	return (0);

}
