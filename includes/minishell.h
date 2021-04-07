/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolasessayan <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 13:23:34 by nicolases         #+#    #+#             */
/*   Updated: 2021/04/07 12:54:13 by adelille         ###   ########.fr       */
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
char			*ft_env_search_advanced(char *str, t_env *env);

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

/*
** prompt
*/

int				ft_prompt_line(void);

/*
** calling command
*/

int				ft_exec_command(char *line, t_env *env);
int				ft_redirection(char *line, int process_num);

/*
** command
*/

int				ft_echo(int fd, t_word *word);
int				ft_cd(char *path);
void			ft_pwd(int fd);
void			ft_env(int fd, t_env *env);

#endif
