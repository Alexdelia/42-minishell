/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolasessayan <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 13:23:34 by nicolases         #+#    #+#             */
/*   Updated: 2021/03/30 18:35:41 by nicolases        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <stdio.h>

# define STDIN 0
# define STDOUT 1
# define STDERR 2

typedef struct	s_cmd {
	char			*str;
	struct s_cmd	*next;
}				t_cmd;

typedef struct	s_env {
	char			*str;
	struct s_env	*next;
}				t_env;

typedef	struct	s_data {
	t_cmd		*cmd;
	t_env		*env;
	int			exit;
}				t_data;

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

#endif
