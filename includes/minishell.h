//
// Created by Marleen Maryjane on 3/19/21.
//

#ifndef MINISHELL_MINISHELL_H
#define MINISHELL_MINISHELL_H
# define BUFFER_SIZE 1
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <math.h>
# include <pthread.h>
# include <errno.h>
# include <stdio.h>


typedef struct		s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

typedef struct	s_main_struct
{
	t_list	*lstcomands;
	t_list *lststrings;

}				t_main_struct;

typedef struct		s_lstobj
{
	int				type;
	void			*obj;
	float			reflective;
	void			*prev;
	void			*next;
}					t_lstobj;

typedef struct s_com
{
	char *komand;
	char **args;
}				t_com;
char	*ft_strchr(const char *s, int c);
size_t	ft_strlen(const char *str);
char	*ft_strdup(const char *s1);
void	*ft_memcpy(void *dst, const void *src, size_t n);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char		**ft_split(char const *s, char c);
void	ft_forsplit(char *line, char k);
char	*ft_strtrim(char const *s1, char const *set);
void ft_pipim(char *command, char **envp);





#endif //MINISHELL_MINISHELL_H
