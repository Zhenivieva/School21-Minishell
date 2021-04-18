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
# include <signal.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <dirent.h>
# include <string.h>
# include <term.h>
# include <termios.h>
# include <termcap.h>

typedef struct 		s_tlist
{
	char *content;
	struct s_tlist *prev;
	struct s_tlist *next;
}					t_tlist;

typedef struct		s_redir
{
	int *geo;

}					t_redir;

typedef struct		s_env
{
	char            *key;
	char 			*content;
	struct s_env	*next;
}					t_env;

typedef struct		s_list
{
    int             type;
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
	char **envp2;
	int  def_fd0;
	int  def_fd1;
//	int append[100];
//	int great[100];
	int less[100];
	int konecg;
//	int nachl;
	t_list *redir;
	char **file;
	t_env *env;
	int 	exit;
	char *oldpwd;
	char *curpwd;
	t_tlist *tail;
	t_tlist *head;
	int	inited;
}				t_com;

int		g_p[2];
t_list				*g_mem;

int		get_next_line(char **line, t_com *com);
char	*ft_strchr(const char *s, int c);
size_t	ft_strlen(const char *str);
char	*ft_strdup(const char *s1);
void	*ft_memcpy(void *dst, const void *src, size_t n);
char	*ft_strjoin(char const *s1, char const *s2);
char	**ft_split(char const *s, char c);
int 	ft_forsplit(char *line, char k);
char	*ft_strtrim(char const *s1, char const *set);
void	ft_pipim(char *command, t_com *com);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_pwd(void);
int		ft_echo(t_com *com);
int		ft_export(t_com *com);
int		ft_unset(t_com *com);
int		ft_cd(t_com *com);
int		ft_env(t_com *com);
int		ft_exit(t_com *com);
int		ft_error(int n);
void	ft_putstr_fd(char *s, int fd);
int		ft_getdollar(char *dollar, t_com *com, int *b, int *a);
char	*ft_getpath(t_com *com);
int 	ft_relabsbin(t_com *com);
//void	parse_word(char *pipecom, t_com *com, t_indexes *inds);
void	parse_word(char *pipecom, t_com *com, t_indexes *inds, int *t);
void	double_quotes(char *pipecom, t_com *com, t_indexes *inds);
int		ft_forexecve(t_com *com);
int		ft_builtin(t_com *com);
void	ft_parsecom(char *pipecom, t_com *com);
void	ft_pipes(t_com *com, char **pipecom, int npipes);
int		ft_atoi(const char *str);
int 	ft_redir(t_com *com);
int 	ft_slash(char *comand);
t_list	*ft_lstnew(void *content, int type);
void	ft_lstadd_back(t_list **lst, t_list *new);
t_list	*ft_lstlast(t_list *lst);
char	*ft_forcontent(char *s, int *inds);
t_env	*ft_lstnew1(char *key, char *content);
void	ft_lstadd_front(t_env **lst, t_env *new);
void	ft_lstadd_front_m(t_list **lst, t_list *new);
void 	ft_forenv(t_com *com, char **envp);
void	ft_putsorted(t_env **lst, t_env *new);
int		ft_strcmp(const char *s1, const char *s2);
void	ft_copyenvp(t_com *com);
char	*ft_strjoin_f(char const *s1, char const *s2);
char	*ft_itoa(int n);
void	ft_shlvlinc(t_com *com);
void	ft_codeforexit(int status, t_com *com);
void    ft_init(t_tlist **tail, t_tlist **head, char *str, t_com *com);
void    insert_beginning(t_tlist **tail, char *str);
char	*ft_substr(char const *s, unsigned int start, size_t len);
void sigint(int num);
void sigquit(int num);
void 	ft_forcat(char **args);


int g_exit;
#endif //MINISHELL_MINISHELL_H
