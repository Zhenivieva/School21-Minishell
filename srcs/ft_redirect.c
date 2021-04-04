//
// Created by Marleen Maryjane on 4/3/21.
//

#include "minishell.h"
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <math.h>
# include <pthread.h>
# include <errno.h>
# include <stdio.h>
# include <sys/types.h>

int ft_redir(t_com *com)
{

	int pid = fork();
//	if (pid == -1)
//		ft_error(7);
	if (pid == 0)
	{
		// dityatko
		int file = open(com->redir->content, O_WRONLY | O_CREAT, 0777);
//		if (file == -1)
//			ft_error(8);
//		printf("The fd to pingResults: %d\n", file);
		int file2 = dup2(file, 1);
		//printf("Test2222");   будет принтить в файл
//		printf ("The duplicated fd: %d\n", file2);
		close(file);

		if (ft_slash(com->args[0]))
			ft_relabsbin(com);
		if (execve(com->args[0], com->args, com->envp) == -1)
			ft_error(6);

//		int err = execve(com->args[0], com->args);
//		if (err == -1)
//		{
//			printf("Could not find program to execute!\n");
//			exit (15);
//		}
		exit(115);
	}
	else
	{
		// Parent process
		int wstatus;
		wait(&wstatus);
		if (WIFEXITED(wstatus))
		{
			int statusCode = WEXITSTATUS(wstatus);
			if (statusCode == 0)
			{
				printf("Success!\n");
			}
			else
				printf("Failure with status code %d!\n", statusCode);
		}
//		printf("Succes!\n");
//		printf("Some port processing goes here!\n");
	}
}
