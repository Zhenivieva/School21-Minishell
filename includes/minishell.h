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
	char **envp;
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
int	ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_pwd(void);
int		ft_echo(t_com *com);
int		ft_export(t_com *com, char **envp);
int		ft_unset(t_com *com, char **envp);
int		ft_cd(t_com *com, char **envp);
int		ft_env(t_com *com, char **envp);
int		ft_exit(char **envp);
int ft_error(int n);
void	ft_putstr_fd(char *s, int fd);
int ft_getdollar(char *dollar, t_com *com, int *b, int *a);
char	*ft_getpath(t_com *com);
void 	ft_relabsbin(t_com *com);





#endif //MINISHELL_MINISHELL_H
