/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaryjan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 12:48:22 by mmaryjan          #+#    #+#             */
/*   Updated: 2021/04/24 12:48:24 by mmaryjan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
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

typedef struct		s_tlist
{
	char			*content;
	struct s_tlist	*prev;
	struct s_tlist	*next;
}					t_tlist;

typedef struct		s_env
{
	char			*key;
	char			*content;
	struct s_env	*next;
}					t_env;

typedef struct		s_list
{
	int				type;
	void			*content;
	struct s_list	*next;
}					t_list;

typedef struct		s_indexes
{
	int				t;
	int				k;
	int				a;
	int				b;
}					t_indexes;

typedef struct		s_com
{
	char			**args;
	char			**envp;
	int				def_fd0;
	int				def_fd1;
	int				konecg;
	int				fork;
	t_list			*redir;
	t_env			*env;
	int				exit;
	char			*oldpwd;
	char			*curpwd;
	t_tlist			*tail;
	t_tlist			*head;
	int				inited;
	int				count;
	int				max;
	char			*buf;
	int				flag;
	t_tlist			*thead;
	t_tlist			*thead2;
	struct termios	term;
	int				npipes;
	int				f;
	int				f2;
}					t_com;

t_list				*g_mem;

void				get_next_line(char **line, t_com *com);
char				*ft_strchr(const char *s, int c);
int					ft_strlen(const char *str);
char				*ft_strdup(const char *s1);
void				*ft_memcpy(void *dst, const void *src, size_t n);
char				*ft_strjoin(char const *s1, char const *s2);
char				**ft_split(char const *s, char c);
int					ft_forsplit(char *line, char k);
char				*ft_strtrim(char const *s1, char const *set);
void				ft_pipim(char *command, t_com *com);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					ft_pwd(void);
int					ft_echo(t_com *com);
int					ft_export(t_com *com);
int					ft_unset(t_com *com);
int					ft_cd(t_com *com);
int					ft_env(t_com *com);
int					ft_exit(t_com *com);
int					ft_error(int n);
void				ft_putstr_fd(char *s, int fd);
int					ft_getdollar(char *dollar, t_com *com, t_indexes *inds);
char				*ft_getpath(t_com *com);
int					ft_relabsbin(t_com *com);
void				parse_word(char *pipecom, t_com *com, t_indexes *inds);
void				double_quotes(char *pipecom, t_com *com, t_indexes *inds);
int					ft_forexecve(t_com *com);
int					ft_builtin(t_com *com);
void				ft_parsecom(char *pipecom, t_com *com);
void				ft_pipes(t_com *com, char **pipecom);
int					ft_atoi(const char *str);
int					ft_redir(t_com *com);
int					ft_slash(char *comand);
t_list				*ft_lstnew(char *content, int type);
void				ft_lstadd_back(t_list **lst, t_list *new);
t_list				*ft_lstlast(t_list *lst);
char				*ft_forcontent(char *s, int *inds);
t_env				*ft_lstnew1(char *key, char *content);
void				ft_forenv(t_com *com, char **envp);
void				ft_putsorted(t_env **lst, t_env *new);
int					ft_strcmp(const char *s1, const char *s2);
void				ft_copyenvp(t_com *com);
char				*ft_strjoin_f(char const *s1, char const *s2);
char				*ft_itoa(int n);
void				ft_shlvl(t_com *com);
void				ft_codeforexit(int status, t_com *com);
void				ft_init(t_tlist **tail, t_tlist **head,
				char *str, t_com *com);
void				insert_beginning(t_tlist **tail, char *str);
void				sigint(int num);
void				sigquit(int num);
int					ft_errno(char *komand, int ex, t_com *com);
void				ft_lstadd_front_m(t_list **lst, t_list *new);
void				ft_left(t_com *com);
int					ft_putchar(int c);
void				ft_up(t_com *com, char **line);
void				ft_right(t_com *com);
void				ft_delete(t_com *com, char **line);
void				ft_home(t_com *com);
void				ft_end(t_com *com);
char				*ft_remove(char *buf, int count);
void				ft_down(t_com *com, char **line);
void				ft_ctrlc(t_com *com, char **line);
void				ft_ctrld(t_com *com);
void				ft_else(t_com *com, char *str, char **line, int res);
void				ft_cicle(t_com *com, char **line);
int					ft_fillredir(t_com *com,
					char *pipecom, int indsk, int type);
int					ft_thirdelse(t_com *com, char *pipecom, t_indexes *inds);
void				ft_firstelse(t_com *com, char *pipecom, t_indexes *inds);
int					ft_kavredir(char *s, int t, int *indk, char *ret);
int					ft_findkey(t_com *com, char *dollar,
				t_indexes *inds, int *ret);
int					ft_numcommand(char *command);
int					ft_numargs(char *command);
void				ft_helpredir(t_com *com);
void				ft_helpfork(t_com *com);
t_list				*ft_lstnew_m1(void *content, int type);

#endif
