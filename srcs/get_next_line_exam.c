#include "minishell.h"

void sighan(int num)
{
	(void)num;
	write(1, "\b\b  \b\b", 6);
	write(1, "\nminishell$", 11);
}

void sighan2(int num)
{
	(void)num;
	write(1, "\b\b  \b\b", 6);
//	write(1, "\nnazhali ctrl-\\\n", 16);
}

int	ft_putchar(int c)
{
	return (write(1, &c, 1));
}

//char *isk_stroka(int fd)
//{
//	char *s;
//	int i;
//	i = 0;
//
//	while (read(fd, &s[i], 1) > 0)
//	{
//		i++;
//
//	}
//}

int get_next_line(char **line, t_com *com)
{
//	char *buf;
//	int i;
	int res;
//	int l;
	char str[2000] = "";
	struct termios term;
	char *term_name = "xterm-256color"; // на айос
	int fd;

	(void)com;

	*line = NULL; //line = NULL
	signal(SIGQUIT, sighan2);
	signal(SIGINT, sighan);

	fd = open("/Users/mflor/history2.txt", O_RDWR | O_CREAT | O_APPEND, 0777);
	tcgetattr(0, &term);
	term.c_lflag &= ~(ECHO);
	term.c_lflag &= ~(ICANON);
	tcsetattr(0, TCSANOW, &term);
	tgetent(0, term_name);  // подгружает базу данных терминалa

	tputs(save_cursor, 1, ft_putchar);

//	i = 0;
//	if (!line || (!(buf = malloc(sizeof(char) * 100000))) || read(0, &buf[0], 0) < 0)
//		return (-1);
//	while ((res = read(0, &buf[i], 1)) >= 0 &&  buf[i] != '\n')
	while (ft_strcmp(str, "\n"))
	{
		// termcaps
		res = read(0, str, 100);
		str[res] = '\0';

		if (ft_strlen(str) == 1)
			write(fd, str, ft_strlen(str));

		if (!strcmp(str, "\e[A"))
		{
			tputs(restore_cursor, 1, ft_putchar);
			tputs(tigetstr("ed"), 1, ft_putchar);

//			if (com->head->next)
//				com->head = com->head->next;
			if (com->head) {

				write(1, com->head->content, ft_strlen(com->head->content));
//				printf("11111111\n");
				if ((*line))
				{
//					printf("-----------------\n");
					if (!(com->inited))
						ft_init(&com->head, &com->tail, *line, com);
					else
						insert_beginning(&com->head, *line);
					free(*line);
				}
//				printf("- - - - - - - - - - - \n");
				*line = ft_strdup(com->head->content);
//				printf("line %s\n", *line);
				if (com->head->next)
					com->head = com->head->next;

			}
//			write(1, "-razdel-", 8);
		}
		else if (!strcmp(str, "\e[B"))
		{
			tputs(restore_cursor, 1, ft_putchar);
			tputs(tigetstr("ed"), 1, ft_putchar);
//			write(1, "next", 4);
			if (com->head) {
				if (com->head->prev)
					com->head = com->head->prev;
				write(1, com->head->content, ft_strlen(com->head->content));
				*line = ft_strdup(com->head->content);
			}
		}
		else if (!strcmp(str, "\177"))
		{
			tputs(cursor_left, 1, ft_putchar);
//			tputs(delete_character, 1, ft_putchar);
			tputs(tgetstr("dc", 0), 1, ft_putchar);
		}
		else
		{
			write (1, str, res);
//			*line = ft_strjoin_f(*line, str);

//			if (!(com->inited))
//				ft_init(&com->head, &com->head, str, com);
//			else
//				insert_beginning(&com->head, str);
			if (ft_strcmp(str, "\n") && ft_strlen(str) == 1)
				*line = ft_strjoin_f(*line, str);

		}

		// termcaps

    }
//	printf("line-%s\n", *line);
//	buf[i] = '\0';
//	if (res != -1)
//		*line  = buf;
//	return (res > 0 ? 1 : res);
//	write(1, "\n", 1);
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

 /*
int	main(void)
{
	int		r;
	char	*line;

	line = NULL;
	while ((r = get_next_line(&line)) > 0)
	{
		printf("%s\n", line);
		free(line);
		line = NULL;
	}
	printf("%s", line);
	free(line);
	line = NULL;
}
 */
