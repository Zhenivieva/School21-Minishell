#include "minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 == *s2 && *s1 && *s2)
	{
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

void	ft_free_el(t_env *to_remove)
{
	if (!to_remove)
		return;
	if (to_remove->content)
		free(to_remove->content);
	if (to_remove->key)
		free(to_remove->key);
	to_remove->next = 0x0;
	free(to_remove);
}

int		ft_unset(t_com *com)
{
	int t;
	t_env *to_remove;
	t_env  *curr;
	t_env  *temp;

	t = 0;
	if (com->env == NULL)
		return (0);
	while (com->args[++t])
	{
		curr = com->env;
		if (!ft_strcmp(curr->key, com->args[t]))
		{
			to_remove = curr;
			curr = curr->next;
			ft_free_el(to_remove);
			continue;
		}
		while (curr->next)
		{
			if (!ft_strcmp(curr->next->key, com->args[t]))
			{
				to_remove = curr->next;
				curr->next = curr->next->next;
				ft_free_el(to_remove);
				continue;
			}
			curr = curr->next;
		}
	}
	return (0);
}