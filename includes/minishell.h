//
// Created by Marleen Maryjane on 3/19/21.
//

#ifndef MINISHELL_MINISHELL_H
#define MINISHELL_MINISHELL_H

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <math.h>
# include <pthread.h>
# include <errno.h>
# include <stdio.h>


typedef struct		s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

typedef struct	s_main_struct
{
	t_list	*lstcomands;
	t_list *lststrings;

}				t_main_struct;

typedef struct		s_lstobj
{
	int				type;
	void			*obj;
	float			reflective;
	void			*prev;
	void			*next;
}					t_lstobj;
#endif //MINISHELL_MINISHELL_H
