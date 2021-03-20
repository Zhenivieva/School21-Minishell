/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaryjan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 11:55:07 by mmaryjan          #+#    #+#             */
/*   Updated: 2021/02/25 21:38:59 by mmaryjan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

# define MAXDIR 200


void		move_by_space(char **stroka)
{
	if (**stroka != ' ' && **stroka != '\t')
		print_errors(-2);
	while (**stroka == ' ' || **stroka == '\t')
		(*stroka)++;
}
/*
void		check_end_of_str(char **stroka)
{
	while (**stroka)
	{
		if (**stroka != ' ' && **stroka != '\t')
			print_errors(-2);
		(*stroka)++;
	}
}
 */

int		parse_string(t_main_struct **base, char *line)
{
	if (line[0] == '\0')
		return (0);
//	else if (line[0] == 'p')
//		return (parse_pwd(base, line));
//	else if (line[0] == 'c')
//		return (parse_cd(base, line));
//	else if (line[0] == 'u')
//		return (parse_unset(base, line));
//	else if (line[0] == 'e' && line[1] == 'c')
//		return (parse_echo(base, line));
//	else if (line[0] == 'e' && line[1] == 'n')
//		return (parse_env(base, line));
//	else if (line[0] == 'e' && line[1] == 'x' && line[1] == 'p')
//		return (parse_export(base, line));
//	else if (line[0] == 'e' && line[1] == 'x' && line[1] == 'i')
//		return (parse_exit(base, line));
	else
		return (-1);
}

t_main_struct	*parse_main(char **copyenvp)
{
	char			*line_temp;
	char			*line;
	t_main_struct	*base;
	int				fd;
	int				i;

	fd = 0;
	base = new_base(copyenvp);
	i = 1;
	while (i > 0)
	{
		write(1, "success_minishell$ ", 19);
		i = get_next_line(fd, &line_temp);
		line = ft_strtrim(line_temp, " ");
		free(line_temp);
		parse_string(&base, line);
		free(line);
	}
	return (base);
}

/*
t_main_struct	*parse_main(char **copyenvp)
{
	int				res;
	char			*line;
	t_main_struct	*base;
	int				fd;

	fd = 0;
	base = new_base(copyenvp);
	while ((res = get_next_line(fd, &line)) > 0)
	{
		//обрезать пробелы в начале string
		if ((res = parse_string(&base, line)) < 0)
			return (NULL);
		free(line);
	}
	free(line);
	//обрезать пробелы в начале string
	if (res < 0 || (res = parse_string(&base, line)) < 0)
		return (NULL);
	return (base);
}
*/