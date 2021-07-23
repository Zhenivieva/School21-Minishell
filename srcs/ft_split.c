/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mflor <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 15:08:16 by mflor             #+#    #+#             */
/*   Updated: 2020/11/11 17:35:02 by mflor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_strlenw(char const *str, int k, char c)
{
	int t;

	t = 0;
	while (str[k] != c && str[k] != '\0')
	{
		k++;
		t++;
	}
	return (t);
}

static char	**proverka(char **ret, int a)
{
	while (a >= 0)
	{
		free(ret[a]);
		a--;
	}
	free(ret);
	return (NULL);
}

static char	**retab(char const *s, char c, char **ret)
{
	int a[3];
	int	t;

	a[0] = 0;
	t = 0;
	while (s[t] != '\0')
	{
		if (s[t] != c && s[t] != '\0')
		{
			a[2] = ft_strlenw(s, t, c);
			if (!(ret[a[0]] = (char*)malloc(a[2] + 1)))
				proverka(ret, a[0]);
			ft_lstadd_front_m(&g_mem, ft_lstnew(ret[a[0]], 0));
			a[1] = 0;
			while (s[t] != c && s[t] != '\0')
				ret[a[0]][a[1]++] = s[t++];
			ret[a[0]][a[1]] = '\0';
			a[0]++;
		}
		if (s[t] != '\0')
			t++;
	}
	ret[a[0]] = NULL;
	return (ret);
}

static int	reta(char const *s, char c)
{
	int		t;
	int		a;

	t = 0;
	a = 0;
	while (s[t] != '\0')
	{
		if (s[t] == c)
			while (s[t] == c && s[t] != '\0')
				t++;
		else if (s[t] != c && s[t] != '\0')
		{
			while (s[t] != c && s[t] != '\0')
				t++;
			a++;
		}
	}
	return (a);
}

char		**ft_split(char const *s, char c)
{
	char	**ret;
	int		wordlen;

	if (s == NULL)
		return (NULL);
	wordlen = reta(s, c);
	ret = (char**)malloc((sizeof(char *) * (wordlen + 1)));
	ft_lstadd_front_m(&g_mem, ft_lstnew_m1(ret, 0));
	if (ret == NULL)
		return (NULL);
	ret = retab(s, c, ret);
	return (ret);
}
