/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolasessayan <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 13:23:34 by nicolases         #+#    #+#             */
/*   Updated: 2021/04/08 12:49:04 by nicolases        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <stdio.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <termios.h>
# include <stdlib.h>

# define STDIN 0
# define STDOUT 1
# define STDERR 2

# define PATH_LEN 512

struct termios orig_termios;

typedef struct	s_hist {
	char			*data;
	struct s_hist	*next;
}				t_hist;

typedef struct	s_env {
	char			*name;
	char			*data;
	struct s_env	*next;
}				t_env;

typedef struct	s_word {
	char			*data;
	struct s_word	*next;
}				t_word;

typedef	struct	s_data {
	t_hist			*hist;
	t_env			*env;
	int				exit;
	int				hc;
	int				ts;
}				t_data;

/*
** hist_utils
*/

t_hist			*new_hist(char *str);
void			add_front_hist(t_hist **hist, t_hist *new);
void			store_hist(t_data *d, char *l);
void			free_one_hist(t_hist *hist);
void			free_all_hist(t_hist *hist);
void			print_hist(t_hist *hist);
int				get_size_hist(t_hist *hist);
char			*get_str_hist(t_hist *hist, int index);
void			pop_hist(t_data *d);

/*
** env_utils
*/

t_env			*new_env(char *str);
t_env			*get_last_env(t_env *env);
void			add_back_env(t_env **env, t_env *new);
t_env			*init_env(char **env);
void			free_one_env(t_env *env);
void			free_all_env(t_env *env);
void			print_env(t_env *env);
char			*ft_env_search(char *str, t_env *env);
t_env			*get_env_by_name(char *name, t_env *env);
int				is_inenv(char *str, t_env *env);
int				get_index_env(t_env *env, char *str);
int				get_size_env(t_env *env);
t_env			*get_env_at_index(t_env *env, int index);
void			remove_index_env(t_env **env, int i);

/*
** word_utils
*/

t_word			*ft_word_split(t_env *env, char *str, int stop);
t_word			*ft_new_word(char *str);
t_word			*ft_get_last_word(t_word *word);
void			ft_add_back_word(t_word **word, t_word *new);
void			ft_free_one_word(t_word *word);
void			ft_free_all_word(t_word *word);
int				ft_word_search(char *str, t_word *word);
int				ft_mi_strcat(char **dst, const char *src, int y, t_env *env);
char			*ft_special_convertion(char *str);

/*
** prompt_utils
*/

int				ft_prompt_line(void);
void			put_cursor_backward(int n);
void			erase_line(char **l);

/*
** engine
*/

void			process_input_printable(char **l, char c);
void			process_input_del(char **l);
void			process_input_newline(t_data *d, char **l);
void			process_arrow_up(t_data *d, char **l);
void			process_arrow_down(t_data *d, char **l);
int				process_input_arrows(t_data *d, char **l);
int				ft_exec_command(char *line, t_data *d);
int				ft_redirection(char *line, int process_num);

/*
** command
*/

int				ft_echo(int fd, t_word *word);
int				ft_cd(char *path);
void			ft_pwd(int fd);
void			ft_env(int fd, t_env *env);
void			ft_export(t_word *word, t_env **env);
int				is_valid_identifier(char *str);
void			print_declare_x(t_env *env);
char			*join_env(t_word *word);
void			ft_unset(t_word *word, t_env **env);

#endif
