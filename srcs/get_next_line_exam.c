/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_exam.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaryjan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 12:30:51 by mmaryjan          #+#    #+#             */
/*   Updated: 2021/04/24 12:30:56 by mmaryjan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint(int num)
{
	(void)num;
	write(1, "^C\n", 3);
}

void	sigquit(int num)
{
	(void)num;
	ft_putstr_fd("^\\Quit: 3\n", 1);
}

int		ft_putchar(int c)
{
	return (write(1, &c, 1));
}

char	*ft_remove(char *buf, int count)
{
	int		t;
	int		k;
	char	*ret;

	ret = malloc(sizeof(char) * ft_strlen(buf));
	if (ret == NULL)
		ft_error(-2);
	ft_lstadd_front_m(&g_mem, ft_lstnew(ret, 0));
	t = 0;
	k = 0;
	while (buf[t])
	{
		if (t == count)
		{
			t++;
			continue;
		}
		ret[k++] = buf[t++];
	}
	ret[k] = '\0';
	return (ret);
}

void	get_next_line(char **line, t_com *com)
{
	*line = NULL;
	tcgetattr(0, &com->term);
	com->term.c_lflag &= ~(ECHO | ICANON | ISIG);
	tcsetattr(0, TCSANOW, &com->term);
	tgetent(0, "xterm-256color");
	tputs(save_cursor, 1, ft_putchar);
	com->thead = com->head;
	com->thead2 = com->head;
	com->max = 0;
	com->count = 0;
	ft_cicle(com, line);
	write(1, "\n", 1);
	com->head = com->thead;
	free(com->buf);
	com->buf = NULL;
	if (ft_strcmp(*line, "") != -1 && ft_strcmp(*line, "") != 0)
	{
		if (!(com->inited))
			ft_init(&com->head, &com->tail, *line, com);
		else
			insert_beginning(&com->head, *line);
	}
	com->term.c_lflag = 0x00000188;
	tcsetattr(0, TCSANOW, &com->term);
}
