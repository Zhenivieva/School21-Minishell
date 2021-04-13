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

int get_next_line(char **line)
{
	char *buf;
	int i;
	int res;

	signal(SIGQUIT, sighan2);
	signal(SIGINT, sighan);
	i = 0;
	if (!line || (!(buf = malloc(sizeof(char) * 100000))) || read(0, &buf[0], 0) < 0)
		return (-1);
	while ((res = read(0, &buf[i], 1)) >= 0 &&  buf[i] != '\n')
	{
//	    signal(SIGINT, sighan);
//		signal(SIGQUIT, sighan2);
		if (i == 0 && res == 0)
		{
			write(1, " exit\n", 6);
			exit(0);
		}
		i++;
    }
	buf[i] = '\0';
	if (res != -1)
		*line  = buf;
	return (res > 0 ? 1 : res);
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
