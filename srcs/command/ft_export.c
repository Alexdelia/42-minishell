/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolasessayan <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 12:06:30 by nicolases         #+#    #+#             */
/*   Updated: 2021/04/06 13:06:24 by nicolases        ###   ########.fr       */
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

void	ft_export(t_word *word, t_env **env)
{
	char	*str;

	str = NULL;
	if (word == NULL)
		print_declare_x(*env);
	else
		str = join_env(word);
	printf("Concat = %s\n", str);
	free(str);
}
