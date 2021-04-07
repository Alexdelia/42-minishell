/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolasessayan <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 18:57:43 by nicolases         #+#    #+#             */
/*   Updated: 2021/04/07 18:57:45 by nicolases        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_declare_x(t_env *env)
{
	while (env != NULL)
	{
		ft_putstr_fd("declare -x ", STDERR);
		ft_putstr_fd(env->name, STDERR);
		ft_putstr_fd("=", STDERR);
		ft_putstr_fd(env->data, STDERR);
		ft_putstr_fd("\n", STDERR);
		env = env->next;
	}
}

char	*join_env(t_word *word)
{
	char	*str;
	char	*tmp;

	str = ft_strdup(word->data);
	while (word->next != NULL)
	{
		tmp = str;
		str = ft_strjoin(tmp, word->next->data);
		free(tmp);
		word = word->next;
	}
	return (str);
}
