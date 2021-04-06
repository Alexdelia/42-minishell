/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolasessayan <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 18:32:39 by nicolases         #+#    #+#             */
/*   Updated: 2021/03/31 09:46:12 by nessayan         ###   ########.fr       */
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
