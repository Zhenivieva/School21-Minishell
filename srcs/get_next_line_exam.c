#include "minishell.h"

void sigint(int num)
{
	(void)num;
	write(1, "^C\n", 3);
}

void sigquit(int num)
{
	(void)num;
	ft_putstr_fd("^\\Quit: 3\n", 1);
}

int	ft_putchar(int c)
{
	return (write(1, &c, 1));
}

char *ft_remove(char *buf, int count)
{
	int t;
	int k;
	char *ret;

	ret = malloc(sizeof(char) * ft_strlen(buf));
	if (ret == NULL)
		ft_error (-2);
	ft_lstadd_front_m(&g_mem, ft_lstnew(ret, 0));
	t = 0;
	k = 0;
	while (buf[t])
	{
		if (t == count) {
			t++;
			continue;
		}
		ret[k++] = buf[t++];
	}
	ret[k] = '\0';
	return (ret);
}

int get_next_line(char **line, t_com *com)
{
	char *buf;
	char *tbuf;
	int res;
	char str[2000] = "";
	struct termios term;
	char *term_name = "xterm-256color"; // на айос
	int count;
	int max;
	int flag;
	int it;
	int it2;

	t_tlist *thead;
	t_tlist *thead2;
	*line = NULL;
	buf = NULL; //buf = NULL


	tcgetattr(0, &term);
	term.c_lflag &= ~(ECHO);
	term.c_lflag &= ~(ICANON);
	term.c_lflag &= ~(ISIG);

	tcsetattr(0, TCSANOW, &term);

	tgetent(0, term_name);  // подгружает базу данных терминалa

	tputs(save_cursor, 1, ft_putchar);
	thead = com->head;
	thead2 = com->head;
	flag = 0;
	count = 0;
	max = 0;
	while (ft_strcmp(str, "\n"))
	{
		res = read(0, str, 100);
		str[res] = '\0';
		if (!ft_strcmp(str, "\e[A"))
		{
			tputs(restore_cursor, 1, ft_putchar);
			tputs(tigetstr("ed"), 1, ft_putchar);

			if (com->head)
			{

				if (buf)  // проверяем, если уже что-то набрано, то записываем в историю
				{
					if (!(com->inited))
					{
						thead2 = com->head;
						com->head = thead;
						ft_init(&com->head, &com->tail, buf, com);
						com->head = thead2;
					}
					else
					{
						thead2 = com->head;
						com->head = thead;
						insert_beginning(&com->head, buf);
						com->head = thead2;
					}
					free(buf);
					buf = NULL;
				}
				if (com->head->next && flag == 1)
					com->head = com->head->next;
				*line = ft_strdup(com->head->content);
				write(1, com->head->content, ft_strlen(com->head->content));
				flag = 1;
				buf = ft_strdup(*line);   // нужно для того. чтобы обратиться с истории и редактировать
				count = ft_strlen(*line);
				max = count;
			}

		}
		else if (!ft_strcmp(str, "\e[H")) //home
		{
			while (count > 0)
			{
				tputs(cursor_left, 1, ft_putchar);
				count--;
			}
		}
		else if (!ft_strcmp(str, "\e[F")) //end
		{
			while (count < max)
			{
				tputs(cursor_right, 1, ft_putchar);
				count++;
			}
		}
		else if (!ft_strcmp(str, "\t"))
		{

		}
		else if (!ft_strcmp(str, "\e[B"))
		{
			tputs(restore_cursor, 1, ft_putchar);
			tputs(tigetstr("ed"), 1, ft_putchar);
			if (com->head) {
				if (com->head->prev)
				{
					com->head = com->head->prev;
					write(1, com->head->content, ft_strlen(com->head->content));
					*line = ft_strdup(com->head->content);
				}
				else
					*line = ft_strdup("");
			}
		}
		else if (!ft_strcmp(str, "\177"))
		{
			if (count > 0)
			{
				tputs(cursor_left, 1, ft_putchar);
				tputs(tgetstr("dc", 0), 1, ft_putchar);
				buf = ft_remove(buf, count-1);
				*line = ft_strdup(buf);
				count--;
				max--;
			}
		}
		else if (!ft_strcmp(str, "\e[D")) //to the left
		{

			if (count > 0)
			{
				tputs(cursor_left, 1, ft_putchar);
				count--;
			}
		}
		else if (!ft_strcmp(str, "\e[C")) //to the right
		{
			if (count < max)
			{
				tputs(cursor_right, 1, ft_putchar);
				count++;
			}
		}
		else if (!ft_strcmp(str, "\4"))
		{
			if (ft_strlen(buf) == 0) {
				write(1, "exit\n", 5);
				exit(0);
			}
		}
		else if (!ft_strcmp(str, "\3"))
		{
			free(*line);
			*line = NULL;
			free(buf);
			buf = NULL;
			write(1, "\nminishell$", 11);
		}
		else if (!ft_strcmp(str, "\034"))
		{
			continue;
		}
		else
		{
			if (flag)
				buf = ft_strdup(*line);
			if (ft_strcmp(str, "\n") && ft_strlen(str) == 1)
			{
				count++;
				max++;
				if (count == max)
				{
					buf = ft_strjoin_f(buf, str);
					write(1, str, res);
				}
				else
				{
					tbuf = malloc(sizeof(char) * (2000)); //leak
					ft_lstadd_front_m(&g_mem, ft_lstnew(tbuf, 0));
					it = 0;
					it2 = 0;
					while (buf[it] && it < max - 1)
					{
						if (it2 == count - 1)
							tbuf[it2++] = str[0];
						else
							tbuf[it2++] = buf[it++];

					}
					tbuf[it2] = '\0';
					free(buf);
					buf = tbuf;

					it = -1;
					while (++it < count - 1)
						tputs(cursor_left, 1, ft_putchar);
					write(1, buf, max);
					it = -1;
					while (++it < max - count)
						tputs(cursor_left, 1, ft_putchar);
				}
			}
			if (ft_strcmp(str, "\n"))
			{

					*line = ft_strdup(buf);
			}
		}
	}
	write (1, "\n", 1);
	com->head = thead;
	free(buf);
	buf = NULL;
	if (ft_strcmp(*line, "") != -1 && ft_strcmp(*line, "") != 0)
	{
		if (!(com->inited))
			ft_init(&com->head, &com->tail, *line, com);
		else
			insert_beginning(&com->head, *line);
	}
	term.c_lflag = 0x00000188;
	tcsetattr(0, TCSANOW, &term);
	return (res);
}


char	*ft_strchr(const char *s, int c)
{
	char	cc;

	cc = (char)c;
	while (*s)
	{
		if (*s == cc)
			return ((char*)s);
		s++;
	}
	if (*s == cc)
		return ((char*)s);
	return ((char*)NULL);
}

