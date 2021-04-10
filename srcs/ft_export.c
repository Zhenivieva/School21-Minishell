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


int 	ft_poiskkey(t_env *env, char *find, char *content)
{
	t_env *temp;

	temp = env;
	while (env)
	{
		if (!(ft_strcmp(env->key, find)))
		{
			env->content = ft_strdup(content);
			env = temp;
			return (0);
		}
		env = env->next;
	}
	env = temp;
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

void ft_zamenashlvl(t_com *com, char *content)
{
	int t;
//	char *temp;
	(void)content;

//	temp = NULL;
	t = -1;
	while(com->envp[++t])
	{
		if (!(ft_strncmp(com->envp[t], "SHLVL", 5)))
		{
			if (com->envp[t] + 6)
			{
				printf("ozhidaem shlvl:%s\n", com->envp[t] + 6);
//				temp = content;
//				content = ft_strdup(com->envp[t] + 6);
//				free(temp);
//				temp = NULL;
				break;
			}
		}
	}
}

int		ft_export(t_com *com)
{
	int t;
//	int k;
//	char *key;
//	char *content;
	char **envstring;
	t_env *temp;
//	int r = -1;
//	while(com->args[++r])
//	{
//		printf("parseceom: args[%d]-%s\n", r, com->args[r]);
//	}
	temp = com->env;
	if (!(com->args[1]))
	{
//		temp = com->env;
		while (com->env)
		{
//			if (!(ft_strcmp(com->env->key, "SHLVL")))
//				ft_zamenashlvl(com, com->env->content);
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
					ft_putsorted(&com->env,
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
	ft_copyenvp(com);
	return (0);
}