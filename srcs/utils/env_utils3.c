/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolasessayan <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 18:53:30 by nicolases         #+#    #+#             */
/*   Updated: 2021/04/09 12:06:11 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		is_inenv(char *str, t_env *env)
{
	while (env != NULL)
	{
		if (ft_strcmp(str, env->name) == 0)
			return (1);
		env = env->next;
	}
	return (0);
}

int		get_index_env(t_env *env, char *str)
{
	int i;

	i = 0;
	while (env != NULL)
	{
		if (ft_strcmp(str, env->name) == 0)
			return (i);
		i++;
		env = env->next;
	}
	return (-1);
}

int		get_size_env(t_env *env)
{
	int	i;

	i = 0;
	while (env != NULL)
	{
		i++;
		env = env->next;
	}
	return (i);
}

t_env	*get_env_at_index(t_env *env, int index)
{
	int i;

	i = 0;
	while (env != NULL)
	{
		if (i == index)
			return (env);
		i++;
		env = env->next;
	}
	return (NULL);
}

void	remove_index_env(t_env **env, int i)
{
	int		l;
	t_env	*t;

	l = get_size_env(*env);
	if (env == NULL || i > l - 1)
		return ;
	if (i == 0)
	{
		t = *env;
		*env = (*env)->next;
		free_one_env(t);
	}
	else if (i == l - 1)
	{
		t = get_last_env(*env);
		get_env_at_index(*env, i - 1)->next = NULL;
		free_one_env(t);
	}
	else
	{
		t = get_env_at_index(*env, i);
		get_env_at_index(*env, i - 1)->next = t->next;
		t->next = NULL;
		free_one_env(t);
	}
}
