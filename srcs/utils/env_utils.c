/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolasessayan <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 18:18:16 by nicolases         #+#    #+#             */
/*   Updated: 2021/04/09 12:05:05 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_env	*new_env(char *str)
{
	int		i;
	t_env	*new;
	char	**split;

	new = malloc(sizeof(t_env));
	split = ft_split(str, '=');
	new->name = split[0];
	new->data = split[1];
	new->next = NULL;
	i = 2;
	while (split[i] != NULL)
	{
		free(split[i]);
		i++;
	}
	free(split);
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
	free(env->name);
	env->name = NULL;
	free(env->data);
	env->data = NULL;
	env->next = NULL;
	free(env);
	env = NULL;
}
