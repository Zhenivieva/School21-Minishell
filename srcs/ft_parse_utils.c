//
// Created by Murch Flor on 3/27/21.
//
#include "minishell.h"

int ft_getdollar(char *dollar, t_com *com, int *b, int *a)
{
	int t;
	int c;
	int ret;
	int perem;
	char *itoa;
	t_env *temp;

	perem = 0;
	if (*dollar == '?')
	{
		itoa = ft_itoa(com->exit);
//		printf("g_exit in get dollar:%d\n", g_exit);
		while ((c = ft_strlen(itoa)) > 0)
		{
			com->args[*a][(*b)++] = *itoa++;
			c--;
		}
		return (2);
	}
	else
	{
		c = 0;
		while (dollar[c] != '\0' && dollar[c] != '$'
			   && dollar[c] != '\\' && dollar[c] != '\''
			   && dollar[c] != '"' && dollar[c] != ' ')
		{
			c++;
		}
		ret = dollar[c] == '\\' ? c + 1 : c;
//добавить реаллок com->args[*a]
//		t = -1;
//		while (com->envp[++t])
//			if (!(ft_strncmp(com->envp[t], dollar, c)))
//			{
//				c++;
//				while (com->envp[t][c])
//					com->args[*a][(*b)++] = com->envp[t][c++];
//			}
		temp = com->env;
		t = 0;
		while (com->env) {
			if (!(ft_strncmp(com->env->key, dollar, (ft_strlen(com->env->key) > c ? (ft_strlen(com->env->key)): c))))
			{
				perem = 1;
				while (com->env->content[t])
					com->args[*a][(*b)++] = com->env->content[t++];
			}
			com->env = com->env->next;
		}
		com->env = temp;
	}
	if (perem == 0)
	{
		com->args[*a][(*b)++] = '$';
		return (1);
	}
	return (ret + 1);
}

char *ft_getpath(t_com *com)
{
	char *path;
	int t;
	int c;
	int a;
	int count;

	a = 0;
	c = 4;
	count = 0;
	t = -1;
	while (com->envp[++t])
		if (!(ft_strncmp(com->envp[t], "PATH", 4)))
		{
			while (com->envp[t][++c])
				count++;
			c = 5;
			path = malloc(count + 1);
			ft_lstadd_front_m(&g_mem, ft_lstnew(path, 0));
			while (com->envp[t][c])
				path[a++] = com->envp[t][c++];
		}
	return (path);
}

int 	ft_relabsbin(t_com *com)
{
	char **paths;
//	char *path;
	int t;
	int flag;
	char *temp;
	char *temp2;

	flag = 0;
	paths = ft_split(ft_getpath(com), ':');
	t = -1;
	while (paths[++t])
	{
		temp = ft_strjoin(paths[t], "/");
		temp2 = ft_strjoin(temp, com->args[0]);
		free (temp);
		if (open(temp2, O_RDONLY) > 0)
		{
			temp = com->args[0];
			com->args[0] = temp2;
			free(temp);
			flag = 1;
			break ;
		}
	}
	if (flag)
		return (1);
	return (0);
}

char	*ft_forcontent(char *s, int *indk)
{
	int t;
	int k;
	char *ret;

	ret = malloc(sizeof(char) * (300)); //заменить на strdup
	ft_lstadd_front_m(&g_mem, ft_lstnew(ret, 0));
	t = 0;
	k = 0;
	if (s[t] == '"')
	{
		while (s[++t] != '"')
		{
			ret[k++] = s[t];
			(*indk)++;
		}
		(*indk)++;
	}
	else if (s[t] == '\'')
	{
		while (s[++t] != '\'')
		{
			ret[k++] = s[t];
			(*indk)++;
		}
		(*indk)++;
	}
	else
	{
		t = -1;
		while (s[++t] && s[t] != ' ' && s[t] != '<' && s[t] != '>') {
			ret[t] = s[t];
			(*indk)++;
		}
	}
	ret[t] = '\0';
//	(*indk)++;

	printf("%s\n", ret);
	return (ret);
}

void parse_word(char *pipecom, t_com *com, t_indexes *inds, int *t)
{
	while (pipecom[inds->k] != ' ' && pipecom[inds->k] != '\0')
	{
		double_quotes(pipecom, com, inds);
		if (pipecom[inds->k] == '\'')
		{
			while (pipecom[++inds->k] != '\'')
				com->args[inds->a][inds->b++] = pipecom[inds->k];
			inds->k++;
		}
		else if (pipecom[inds->k] == '$')
		{
			if (pipecom[inds->k + 1] != '\0')
			{
				inds->k = inds->k + ft_getdollar(pipecom + inds->k + 1, com, &inds->b, &inds->a); //&inds
				continue;
			}
			else
				com->args[inds->a][inds->b++] = pipecom[inds->k++];

		}
		else if (pipecom[inds->k] != '$')
		{
			if (pipecom[inds->k] == '<')
			{
				inds->k++;
				while(pipecom[inds->k] == ' ')
					inds->k++;
//				com->less[inds->a + 1] = 1;
				com->konecg++;
                ft_lstadd_back(&com->redir, ft_lstnew(ft_forcontent(pipecom + inds->k, &inds->k), 1));
//				com->file[(*t)++] = ft_strdup(ft_forcontent(pipecom + inds->k, &inds->k));
//				inds->k++;
				break;
			}
			if (pipecom[inds->k] == '>' && pipecom[inds->k + 1] == '>')
			{
				inds->k = inds->k + 2;
				while(pipecom[inds->k] == ' ')
					inds->k++;
//				com->less[inds->a + 1] = 2;
				com->konecg++;
				ft_lstadd_back(&com->redir, ft_lstnew(ft_forcontent(pipecom + inds->k, &inds->k), 3));
//				com->file[*t++] = ft_strdup(ft_forcontent(pipecom + inds->k, &inds->k));
//				inds->k++;
				break;
			}
			if (pipecom[inds->k] == '>' && pipecom[inds->k + 1] != '>')
			{
				inds->k++;
				while(pipecom[inds->k] == ' ')
					inds->k++;
//				com->less[inds->a + 1] = 3;
				com->konecg++;
//				com->file[*t++] = (ft_forcontent(pipecom + inds->k, &inds->k));
				ft_lstadd_back(&com->redir, ft_lstnew(ft_forcontent(pipecom + inds->k, &inds->k), 2));
//				inds->k++;
				break;
			}
			com->args[inds->a][inds->b++] = pipecom[inds->k++];
			(void)t;
		}
	}
}