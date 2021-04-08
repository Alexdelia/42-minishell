/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolasessayan <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 11:20:07 by nicolases         #+#    #+#             */
/*   Updated: 2021/04/08 13:41:17 by nicolases        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	get_index_env(t_env *env, char *str)
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

int	get_size_env(t_env *env)
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
	t_env		*t;

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

void	ft_unset(t_word *word, t_env **env)
{
	char	*str;
	int	i;

	if (word == NULL)
		return ;
	str = join_env(word);
	printf("Word=%s\n", str);
	if (is_valid_identifier(str) == 0 || is_included(str, '=') == 1)
	{
		free(str);
		return (ft_putstr_fd("\033[1;31mNot a valid identifier\n", STDERR));
	}
	if (is_inenv(str, *env) == 1)
	{
		i = get_index_env(*env, str);
		printf("i = %d\n", i);
		remove_index_env(env, i);
	}
	return (free(str));
}
