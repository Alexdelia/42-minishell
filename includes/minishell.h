/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolasessayan <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 13:23:34 by nicolases         #+#    #+#             */
/*   Updated: 2021/03/31 10:50:34 by nessayan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <stdio.h>

# define STDIN 0
# define STDOUT 1
# define STDERR 2

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
}				t_data;

/*
** hist_utils
*/

t_hist			*new_hist(char *str);
t_hist			*get_last_hist(t_hist *hist);
void			add_back_hist(t_hist **hist, t_hist *new);
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

/*
** word_utils
*/

t_word			*new_word(char *str);
t_word			*get_last_word(t_word *word);
void			ft_add_back_word(t_word **word, t_word *new);
void			ft_free_one_word(t_word *word);
void			ft_free_all_word(t_word *word);

/*
** command
*/

int				ft_echo(int fd, t_word *word, t_env *env);
int				ft_cd(char *path);
void			ft_pwd(int fd);

/*
** search in lst
*/

char			*ft_env_search(char *str, t_env env);
int				ft_word_search(t_word word, char *str);

#endif
