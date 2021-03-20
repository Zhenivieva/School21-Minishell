#include "minishell.h"

int	parse_pwd(t_scene **base, char *line)
{

	if (!(ft_strncmp(line, "pwd", 4)))
	{
		getcwd(dir, MAXDIR);
		printf("%s\n", dir);
	}
}