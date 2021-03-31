/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 18:32:23 by adelille          #+#    #+#             */
/*   Updated: 2021/03/31 06:50:12 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#define PATH_LEN 512

void	ft_pwd(int fd)
{
	char	path[PATH_LEN];

	getcwd(path, PATH_LEN - 1);
	ft_putstr_fd(path, fd);
}
