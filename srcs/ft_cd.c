/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 18:19:32 by adelille          #+#    #+#             */
/*   Updated: 2021/03/30 18:32:09 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cd(char *path)
{
	if (chdir(path) == -1)
	{
		ft_putstr_fd("Error:\t", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(" not found\n", 2);
		return (FALSE);
	}
	return (TRUE);
}
