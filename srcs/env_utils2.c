/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolasessayan <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 18:32:39 by nicolases         #+#    #+#             */
/*   Updated: 2021/03/30 18:33:03 by nicolases        ###   ########.fr       */
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
		printf("%s\n", env->str);
		env = env->next;
	}
}
