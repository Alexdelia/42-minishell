/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolasessayan <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 13:23:34 by nicolases         #+#    #+#             */
/*   Updated: 2021/04/27 14:23:56 by adelille         ###   ########.fr       */
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
# include <curses.h>
# include <term.h>

# define STDIN 0
# define STDOUT	1
# define STDERR	2
# define TERMCAP 0

# define PATH_LEN	512

int	g_status;

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
	t_word			*word;
	int				exit;
	int				hc;
	int				ts;
	struct termios	orig_termios;
}				t_data;

typedef struct	s_parser {
	int				i;
	int				y;
}				t_parser;

/*
** engine
*/

void			enable_raw_mode(t_data *d);
void			process_input_printable(char **l, char c);
void			process_input_del(char **l);
void			process_input_newline(t_data *d, char **l);
void			process_arrow_up(t_data *d, char **l);
void			process_arrow_down(t_data *d, char **l);
int				process_input_arrows(t_data *d, char **l);
void			process_ctrl_c(void);
void			process_ctrl_d(t_data *d);
void			ft_exec_command(char *line, t_data *d);
int				ft_parse_exec(t_word *word, t_data *d);
void			ft_pipe(char *line, t_data *d, int process_num, int **pfd);
void			ft_chevron(char *line, t_data *d, int *process_num, int **pfd);
void			ft_semi(char *line, t_data *d, int process_num, int **pfd);

/*
** command
*/

int				ft_echo(t_word *word);
int				ft_cd(char *path);
int				ft_pwd(void);
int				ft_env(t_env *env);
int				ft_export(t_word *word, t_env **env);
int				is_valid_identifier(char *str);
int				print_declare_x(t_env *env);
char			*join_env(t_word *word);
char			**split_export(char *str);
int				ft_unset(t_word *word, t_env **env);
int				ft_exec(t_word *word, t_env *env);
int				ft_statable(t_word **word, t_env *env);
int				ft_exit(t_data *d);

/*
** engine utils
*/

int				ft_fd_out(char *line, int process_num, char char_stop);
int				ft_fd_in(char *line, int process_num);
int				check_build_fd(char *line, int process_num, int **pfd);
char			ft_char_stop(char *line, int process_num);
void			move_word(char *line, t_data *d, int process_num, int n);
int				**init_pfd(int c);
void			free_pfd(int **pfd, int c);
int				ft_count_process(char *line);
int				ft_chevron_count(char *line, int process_num);
int				ft_reverse_count(char *line, int process_num);
int				forward_to_semi(char *line, int process_num);
int				redir_errall(char *line);
int				ft_syntax_error(char *line, int i, int way);

/*
** prompt_utils
*/

int				ft_prompt_line(void);
void			put_cursor_backward(int n);
void			erase_line(char **l);
int				ft_mi_error(char *command, char *text, int va_error);
int				init_term(void);

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
char			**etoa(t_env *env);

/*
** word_utils
*/

int				ft_word_split(t_data *d, char *str, int stop);
int				get_start_index(char *line, int process_num, int quote);
int				ft_strlen_post_transform(const char *str, t_data *d, int ml);
int				ft_transform(t_data *d, char *str, int first);
void			ft_conv_simple(t_parser *p, const char *str, char *res);
void			ft_conv_double(t_parser *p, t_data *d,
				const char *str, char **res);
void			ft_conv_dollar(t_parser *p, t_data *d,
				const char *str, char **res);
int				ft_len_inner_trans(t_parser *p, const char *str, int ml);
int				ft_inner_trans(t_parser *p, const char *str,
				char **res, int ml);
void			ft_loop_trans(t_parser *p, t_data *d,
				const char *str, char *res);
t_word			*ft_new_word(char *str);
t_word			*ft_get_last_word(t_word *word);
void			ft_add_back_word(t_word **word, t_word *new);
void			ft_add_front_word(t_word **word, t_word *new);
void			ft_free_one_word(t_word *word);
void			ft_free_all_word(t_word *word);
int				ft_word_search(char *str, t_word *word);
int				ft_mi_strcat(char **dst, const char *src, int y, t_data *d);
char			*ft_special_convertion(char *str);
void			ft_print_word(t_word *word);
int				ft_char_quote(char *line, int i);

#endif
