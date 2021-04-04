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
# include <sys/types.h>

typedef struct		s_redir
{
	int *geo;

}					t_redir;

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


typedef struct s_indexes
{
	int	t;
	int k;
	int a;
	int b;
}				t_indexes;


typedef struct s_com
{
	char **args;
	char **envp;
	int  def_fd0;
	int  def_fd1;
	int append[100];
	int great[100];
	int less[100];
	int konecg;
	int nachl;
}				t_com;

int get_next_line(char **line);
char	*ft_strchr(const char *s, int c);
size_t	ft_strlen(const char *str);
char	*ft_strdup(const char *s1);
void	*ft_memcpy(void *dst, const void *src, size_t n);
char	*ft_strjoin(char const *s1, char const *s2);
char	**ft_split(char const *s, char c);
int 	ft_forsplit(char *line, char k);
char	*ft_strtrim(char const *s1, char const *set);
void	ft_pipim(char *command, char **envp);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_pwd(void);
int		ft_echo(t_com *com);
int		ft_export(t_com *com, char **envp);
int		ft_unset(t_com *com, char **envp);
int		ft_cd(t_com *com, char **envp);
int		ft_env(t_com *com, char **envp);
int		ft_exit(t_com *com);
int		ft_error(int n);
void	ft_putstr_fd(char *s, int fd);
int		ft_getdollar(char *dollar, t_com *com, int *b, int *a);
char	*ft_getpath(t_com *com);
int 	ft_relabsbin(t_com *com);
void	parse_word(char *pipecom, t_com *com, t_indexes *inds);
void	double_quotes(char *pipecom, t_com *com, t_indexes *inds);
int		ft_forexecve(t_com *com);
int		ft_builtin(t_com *com);
void	ft_parsecom(char *pipecom, t_com *com);
void	ft_pipes(t_com *com, char **pipecom, int npipes);
int		ft_atoi(const char *str);
int ft_redir(t_com *com);
int ft_slash(char *comand);






#endif //MINISHELL_MINISHELL_H
