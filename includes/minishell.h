
#ifndef MINISHELL_H
#define MINISHELL_H

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <math.h>
# include <pthread.h>
# include <errno.h>
# include <stdio.h>
#include <string.h> // убрать, заменить ф-циями из libft


typedef struct		s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

typedef struct	s_main_struct
{
	t_list	*lstcomands;
	t_list	*lstenvp;
	int 	flag_cov2;
	int 	flag_cov1;
}				t_main_struct;

typedef struct		s_lstobj
{
	int				type;
	void			*obj;
	void			*prev;
	void			*next;
}					t_lstobj;

/* parsing:      */
t_main_struct	*parse_main(char **copyenvp);
t_main_struct	*new_base(char **envp);


/* utils:        */
int	ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strtrim(char const *s1, char const *set);
void	ft_putstr_fd(char *s, int fd);

/* gnl:          */
# define BUFFER_SIZE 1
int		get_next_line(int fd, char **line);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strdup(const char *s1);
char	*ft_strchr(const char *s, int c);
size_t	ft_strlen(const char *str);
void	*ft_memcpy(void *dst, const void *src, size_t n);
char	*ft_substr(char const *s, unsigned int start, size_t len);


/* main:        */
void	print_errors(int ernum, char *line);


/* free:        */
void	free_and_null(void **ptr);

#endif
