/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 10:09:57 by adelille          #+#    #+#             */
/*   Updated: 2021/04/20 10:11:36 by nicolases        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_env(t_env *env)
{
	while (env)
	{
		ft_putstr_fd(env->name, STDOUT);
		ft_putstr_fd("=", STDOUT);
		ft_putstr_fd(env->data, STDOUT);
		ft_putstr_fd("\n", STDOUT);
		env = env->next;
	}
	return (0);
}
