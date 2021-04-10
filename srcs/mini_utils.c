//
// Created by Marleen Maryjane on 4/9/21.
//

#include "minishell.h"

int	ft_lstsize(t_env *lst)
{
	int size;

	size = 0;
	while (lst != NULL)
	{
		lst = lst->next;
		size++;
	}
	return (size);
}

int		ft_kolenvp(char **envp)
{
	int t;
	int c;

	t = -1;
	c = 0;
	while (envp[++t])
		c++;
//	printf("kolichestvo-%d\n", c);
	return (c);
}

void	ft_copyenvp(t_com *com)
{
	t_env	*temp;
	int		t;
	char	*temp2;

	temp = com->env;
	com->envp = malloc(sizeof (char *) * (ft_lstsize(com->env) + 1));
	if (!(com && com->envp))
		ft_error(-2);
	t = -1;
//	while (envp[++t])
//		com->envp[t] = ft_strdup(envp[t]);
//	com->envp[t] = NULL;
	while (com->env)
	{
		temp2 = ft_strjoin("=", com->env->content);
		com->envp[++t] = ft_strjoin_f(com->env->key, temp2);
//		free (temp2); //to clean leak, but it segs with this srting
		if (!(ft_strcmp(com->env->key, "SHLVL")))
		{
			printf("Vot pozhalusta tut stroka takoi na vsaiki eto com->envp[%d]:%s\n", t, com->envp[t]);
			printf("A tut ya takoi:%s\n", com->env->content);
		}
		com->env = com->env->next;
	}
	com->envp[++t] = NULL;
	com->env = temp;
}

void	ft_copyenvp2(t_com *com)
{
	t_env	*temp;
	int		t;
	char	*temp2;

	temp = com->env;
	com->envp2 = malloc(sizeof (char *) * (ft_lstsize(com->env) + 1));
	if (!(com && com->envp2))
		ft_error(-2);
	t = -1;
//	while (envp[++t])
//		com->envp[t] = ft_strdup(envp[t]);
//	com->envp[t] = NULL;
	while (com->env)
	{
		temp2 = ft_strjoin("=", com->env->content);
		com->envp2[++t] = ft_strjoin_f(com->env->key, temp2);
		free (temp2); //to clean leak, but it segs with this srting
		if (!(ft_strcmp(com->env->key, "SHLVL")))
		{
			printf("Vot pozhalusta tut stroka takoi na vsaiki eto com->envp[%d]:%s\n", t, com->envp2[t]);
			printf("A tut ya takoi:%s\n", com->env->content);
		}
		com->env = com->env->next;
	}
	com->envp2[++t] = NULL;
	com->env = temp;
}