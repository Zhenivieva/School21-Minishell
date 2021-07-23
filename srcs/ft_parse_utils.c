/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaryjan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 12:19:58 by mmaryjan          #+#    #+#             */
/*   Updated: 2021/04/24 12:20:00 by mmaryjan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_getdollar(char *dollar, t_com *com, t_indexes *inds)
{
	int		c;
	int		ret;
	int		perem;
	char	*itoa;

	perem = 0;
	if (*dollar == '?')
	{
		itoa = ft_itoa(com->exit);
		while ((c = ft_strlen(itoa)) > 0)
		{
			com->args[inds->a][inds->b++] = *itoa++;
			c--;
		}
		return (2);
	}
	else
		perem = ft_findkey(com, dollar, inds, &ret);
	if (perem == 0 && dollar[0] == ' ')
	{
		com->args[inds->a][inds->b++] = '$';
		return (1);
	}
	return (ret + 1);
}

char	*ft_getpath(t_com *com)
{
	char	*path;
	int		t;
	int		c;
	int		a;
	int		count;

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

int		ft_relabsbin(t_com *com)
{
	char	**paths;
	int		t;
	int		flag;
	char	*temp;
	char	*temp2;

	flag = 0;
	paths = ft_split(ft_getpath(com), ':');
	t = -1;
	while (paths[++t])
	{
		temp = ft_strjoin(paths[t], "/");
		temp2 = ft_strjoin(temp, com->args[0]);
		free(temp);
		if (open(temp2, O_RDONLY) > 0)
		{
			temp = com->args[0];
			com->args[0] = temp2;
			free(temp);
			flag = 1;
		}
	}
	if (flag)
		return (1);
	return (0);
}

char	*ft_forcontent(char *s, int *indk)
{
	int		t;
	char	*ret;

	ret = malloc(sizeof(char) * (300));
	ft_lstadd_front_m(&g_mem, ft_lstnew(ret, 0));
	t = -1;
	if (ft_kavredir(s, 0, indk, ret))
	{
		while (s[++t] && s[t] != ' ' && s[t] != '<' && s[t] != '>')
		{
			ret[t] = s[t];
			(*indk)++;
		}
	}
	ret[t] = '\0';
	return (ret);
}

void	parse_word(char *pipecom, t_com *com, t_indexes *inds)
{
	while (pipecom[inds->k] != ' ' && pipecom[inds->k] != '\0')
	{
		double_quotes(pipecom, com, inds);
		if (pipecom[inds->k] == '\'')
			ft_firstelse(com, pipecom, inds);
		else if (pipecom[inds->k] == '$')
		{
			if (pipecom[inds->k + 1] != '\0')
			{
				inds->k = inds->k +
					ft_getdollar(pipecom + inds->k + 1, com, inds);
				continue;
			}
			else
				com->args[inds->a][inds->b++] = pipecom[inds->k++];
		}
		else if (pipecom[inds->k] != '$' && pipecom[inds->k] != '"')
		{
			if (ft_thirdelse(com, pipecom, inds))
				break ;
			com->args[inds->a][inds->b++] = pipecom[inds->k++];
		}
		ft_thirdelse(com, pipecom, inds);
	}
}
