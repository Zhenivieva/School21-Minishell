//
// Created by mac on 30.03.2021.
 #include "minishell.h"
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <math.h>
# include <pthread.h>
# include <errno.h>
# include <stdio.h>
# include <sys/types.h>

void	ft_closefd(int npipes, int pipes[npipes][2])
{
	int j = -1;
	while (++j < npipes)
	{
		close(pipes[j][0]);
		close(pipes[j][1]);
	}
}

 void	ft_pipes(t_com *com, char **pipecom, int npipes)
{
    int i;
    int cpid;
    int pids[npipes];
    int pipes[npipes][2];

	dup2(0, com->def_fd0);
	dup2(1, com->def_fd1);
	i = -1;
    while (++i < npipes)
    {
        if (pipe(pipes[i]) == -1)
        {
            printf("Erorr with creating pipe\n");
            exit(-5);
        }
    }
    i = -1;
    while (++i < npipes)
    {
        pids[i] = fork();
        if (pids[i] == -1)
        {
            printf("Error with creating process %d", i);
            exit (3);
        }
        if (pids[i] == 0)
        {
			if (i == 0)
				dup2(pipes[i][1], 1);
			else if (i < npipes - 1 && i > 0)
			{
				dup2(pipes[i - 1][0], 0);
				dup2(pipes[i][1], 1);
			}
			else if (i == npipes - 1)
				dup2(pipes[i - 1][0], 0);
			ft_closefd(npipes, pipes);
			ft_parsecom(pipecom[i], com);
			if (ft_builtin(com))
				(ft_forexecve(com));
			exit(11);
        }
    }
	ft_closefd(npipes, pipes);
    i = -1;
	while (++i < npipes)
		waitpid(pids[i], NULL, 0);
	dup2(com->def_fd0, 0);
	dup2(com->def_fd1, 1);
}
