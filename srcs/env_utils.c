/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolasessayan <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 18:18:16 by nicolases         #+#    #+#             */
/*   Updated: 2021/03/30 18:22:01 by nicolases        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_env	*new_env(char *str)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	new->str = ft_strdup(str);
	new->next = NULL;
	return (new);
}

t_env	*get_last_env(t_env *env)
{
	if (env == NULL)
		return (env);
	while (env->next != NULL)
		env = env->next;
	return (env);
}

void	add_back_env(t_env **env, t_env *new)
{
	t_env	*l;

	l = get_last_env(*env);
	if (l != NULL)
		l->next = new;
	else
		*env = new;
}

t_env	*init_env(char **env)
{
	t_env	*top;
	t_env	*new;
	int		i;

	if (env[0] != NULL)
		top = new_env(env[0]);
	i = 1;
	while (env[i] != NULL)
	{
		new = new_env(env[i]);
		add_back_env(&top, new);
		i++;
	}
	return (top);
}

void	free_one_env(t_env *env)
{
	free(env->str);
	env->str = NULL;
	env->next = NULL;
	free(env);
	env = NULL;
}
