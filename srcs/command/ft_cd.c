/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 18:19:32 by adelille          #+#    #+#             */
/*   Updated: 2021/04/24 11:52:34 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_cd(char *path)
{
	ft_pserc("CD\nPath: ", RED);
	ft_pserc(path, RED);
	ft_pserc("\n", RED);
	if (chdir(path) == -1)
		return (ft_mi_error("cd", "No such file or directory", 1));
	ft_pwd();
	return (0);
}
