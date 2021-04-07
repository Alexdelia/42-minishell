/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolasessayan <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 18:32:39 by nicolases         #+#    #+#             */
/*   Updated: 2021/04/07 15:16:14 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_all_env(t_env *env)
{
	t_env *t;

	while (env != NULL)
	{
		t = env;
		env = t->next;
		free_one_env(t);
	}
}

void	print_env(t_env *env)
{
	while (env != NULL)
	{
		printf("%-30s:%s\n", env->name, env->data);
		env = env->next;
	}
}

char	*ft_env_search(char *str, t_env *env)
{
	while (env != NULL)
	{
		if (ft_strcmp(str, env->name) == 0)
			return (env->data);
		env = env->next;
	}
	return ("\0");
}

char	*ft_special_convertion(char *str)
{
	char	path[PATH_LEN];

	if (str[0] == '~' && !str[1])
		return (getcwd(path, PATH_LEN - 1));
	return (str);
}
