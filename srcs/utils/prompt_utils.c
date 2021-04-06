/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 10:39:17 by adelille          #+#    #+#             */
/*   Updated: 2021/04/06 15:27:30 by nicolases        ###   ########.fr       */
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

void	put_cursor_backward(int n)
{
	int i;

	i = 0;
	while (i < n)
	{
		ft_putstr_fd("\x1b[1D", STDIN);
		i++;
	}
	ft_putstr_fd("\x1b[K", STDIN);
}

void	erase_line(char **l)
{
	int size;

	size = ft_strlen(*l);
	put_cursor_backward(size);
	free(*l);
	*l = NULL;
}
