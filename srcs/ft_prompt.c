/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 10:39:17 by adelille          #+#    #+#             */
/*   Updated: 2021/04/02 11:06:05 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		ft_prompt_line(void)
{
	char	path[PATH_LEN];
	int		i;
	int		y;

	getcwd(path, PATH_LEN - 1);
	i = 0;
	y = 0;
	while (path[i])
	{
		if (path[i] == '/')
			y = i;
		i++;
	}
	ft_pserc("➜  ", GRN);
	ft_pserc("minishell ", "\033[1;36m");
	ft_pserc(&path[y + 1], BIMAG);
	ft_pserc(" ▸ ", "\033[1;36m");
	return (0);
}
