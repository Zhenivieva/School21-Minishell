//
// Created by Marleen Maryjane on 4/8/21.
//

#include "minishell.h"
//void make_env_list(t_com *com)
//{
//	com->env = malloc(sizeof(t_env));
//
//	int t;
////	char *key;
////	char *content;
//	char **envstring;
//
//	t = -1;
//	while(com->envp[++t])
//	{
//		envstring = ft_split(com->envp[t], '=');
//
//	}
//}

void 	ft_sortenv(t_env *env)
{

}

int 	ft_poiskkey(t_env *env, char *find, char *content)
{
	while (env)
	{
		if (!(ft_strncmp(env->key, find, ft_strlen(find))))
		{
			env->content = ft_strdup(content);
			return (0);
		}
		env = env->next;
	}
	return (1);
}

int 	ft_parsearg(char *key)
{
	if ((*key <= '9' && *key >= '0') || *key == '=')
	{
		write(1, "minishell: export: `",20);
		ft_putstr_fd(key, 1);
		write(1, "' : not a valid identifier\n", 28);
		return (0);
	}
	return (1);
}

int		ft_export(t_com *com)
{
	int t;
	int k;
//	char *key;
//	char *content;
	char **envstring;
	t_env *temp;

	temp = com->env;
	if (!(com->args[1]))
	{
//		temp = com->env;
		while (com->env)
		{
			write(1, "declare -x ", 11);
			ft_putstr_fd(com->env->key, 1);
			if (com->env->content)
			{
				write(1, "=\"", 2);
				ft_putstr_fd(com->env->content, 1);
				write(1, "\"", 1);
			}
			write(1, "\n", 1);
			com->env = com->env->next;
		}
		com->env = temp;

	}
	else
	{
		t = 0;
		while (com->args[++t])
		{
			printf("args[%d]-%s\n", t, com->args[t]);
			if (ft_parsearg(com->args[t]))
			{
				envstring = ft_split(com->args[t], '=');
				if (ft_poiskkey(com->env, envstring[0], envstring[1]))
					ft_lstadd_back1(&com->env,
									ft_lstnew1(envstring[0], envstring[1]));
				com->env = temp;
			}
		}

//		while (com->env)
//		{
//			write(1, "declare -x ", 11);
//			ft_putstr_fd(com->env->key, 1);
//			write(1, "=\"", 2);
//			ft_putstr_fd(com->env->content, 1);
//			write(1, "\"\n", 2);
//			com->env = com->env->next;
//		}
	}
//	com->env = temp;
//	while (com->env)
//	{
//		write(1, "declare -x ", 11);
//		ft_putstr_fd(com->env->key, 1);
//		write(1, "=\"", 2);
//		ft_putstr_fd(com->env->content, 1);
//		write(1, "\"\n", 2);
//		com->env = com->env->next;
//	}
//	ft_sortenv(com->env);
	return (0);
}