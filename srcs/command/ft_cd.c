/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 18:19:32 by adelille          #+#    #+#             */
/*   Updated: 2021/04/26 10:55:03 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_cd(char *path)
{
	int	i;

	if (!path[0])
		return (0);
	i = 0;
	if (chdir(path) == -1)
	{
		while (path[i])
		{
			if (path[i] == ' ')
				return (ft_mi_error("cd", "too many argumetns", 1));
			i++;
		}
		return (ft_mi_error("cd", "No such file or directory", 1));
	}
	return (0);
}
