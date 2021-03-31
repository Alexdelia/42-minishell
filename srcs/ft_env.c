/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 10:09:57 by adelille          #+#    #+#             */
/*   Updated: 2021/03/31 12:14:31 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(int fd, t_env env)
{
	while (env)
	{
		ft_putstr_fd(env->name, fd);
		ft_putstr_fd("=", fd);
		ft_putstr_fd(env->data, fd);
		ft_putstr_fd("\n", fd);
		env = env->next;
	}
	if (fd != STDOUT)
		close(fd);
}
