#include "minishell.h"

t_main_struct	*new_base(char **envp)
{
	t_main_struct *base;

	if (!(base = malloc(sizeof(t_main_struct))))
		print_errors(-6, "");
	base->lstcomands = NULL;
	base->lstenvp = envp;
	//base->struct1 = NULL;
	base->flag_cov2 = 0;
	base->flag_cov1 = 0;
	return (base);
}

// ft free_and_null(void **ptr) is used for free base
/*
void free_base(t_main_struct *base)
{

}
 */