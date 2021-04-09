/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 18:32:23 by adelille          #+#    #+#             */
/*   Updated: 2021/04/09 11:08:18 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		ft_pwd(int fd)
{
	char	path[PATH_LEN];

	getcwd(path, PATH_LEN - 1);
	ft_putstr_fd(path, fd);
	ft_putstr_fd("\n", fd);
	if (fd != STDOUT)
		close(fd);
	return (0);
}
