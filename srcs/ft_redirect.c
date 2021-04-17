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

void ft_codeforexit(int status, t_com *com)
{
	if (status == 0)
		com->exit = 0;
	else if (status == 256)
		com->exit = 1;
	else
		com->exit = status >> 8;
}

int ft_redir(t_com *com)
{
	t_list *temp;
    int file;
    int file2;
	dup2(0, com->def_fd0);
	dup2(1, com->def_fd1);
//    temp = com->redir;
	int pid = fork();
//	if (pid == -1)
//		ft_error(7);
	if (pid == 0)
	{
		// dityatko
		temp = com->redir;
        while (com->redir)
        {
            if (com->redir->type == 1) {
                file = open(com->redir->content, O_RDONLY);
                file2 = dup2(file, 0);
                ft_putstr_fd("file=%d\n", 1);
            }
            else if (com->redir->type == 2)
            {
                file = open(com->redir->content, O_WRONLY | O_CREAT, 0777);
                file2 = dup2(file, 1);
            }
            else if (com->redir->type == 3)
            {
                file = open(com->redir->content, O_WRONLY | O_APPEND);
                file2 = dup2(file, 1);
            }
//            if (file == -1)
//                ft_error(8);
            close(file);
			if (file == -1)
			{
				dup2(com->def_fd1, 1);
				ft_error(8);
			}
            com->redir = com->redir->next;
        }
		com->redir = temp;
        if (ft_builtin(com))
        {
            if (ft_slash(com->args[0]))
                ft_relabsbin(com);
            if (execve(com->args[0], com->args, com->envp) == -1)
                ft_error(6);
        }


		com->exit = 15;
		exit(com->exit);
	}
	else
	{
		int wstatus;
		wait(&wstatus);
		if (WIFEXITED(wstatus))
			ft_codeforexit(wstatus, com);
//		{
//			int statusCode = WEXITSTATUS(wstatus);
//			if (statusCode == 0)
//			{
//				printf("Success!\n");
//			}
//			else
//				printf("Failure with status code %d!\n", statusCode);
//		}
//		printf("Succes!\n");
//		printf("Some port processing goes here!\n");
	}
//	com->redir = temp;
	return (0);
}
