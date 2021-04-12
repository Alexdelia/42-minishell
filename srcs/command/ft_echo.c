/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 17:41:22 by adelille          #+#    #+#             */
/*   Updated: 2021/04/12 16:51:01 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*static int	ft_ps_but_one_c(char *str, char c, int fd)
{
	int	is_c;
	int	i;

	i = 0;
	while (str[i])
	{
		
		i++;
	}
}*/

int			ft_echo(int fd, t_word *word)
{
	int	i;

	i = 0;
	if (word->data[0] == '-')
	{
		i++;
		while (word->data[i] && word->data[i] == 'n')
			i++;
		if (word->data[i] != ' ')
			i = 0;
		else
			i++;
	}
	//ft_ps_but_one_c(&word->data[i], ' ', fd);
	i = 0;
	if (word->data[0] == '-')
	{
		i++;
		while (word->data[i] && word->data[i] == 'n')
			i++;
		if (!word->data[i] || word->data[i] == ' ')
			return (0);
	}
	ft_putstr_fd("\n", fd);
	return (0);
}
