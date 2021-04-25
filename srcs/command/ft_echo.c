/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 17:41:22 by adelille          #+#    #+#             */
/*   Updated: 2021/04/25 13:57:04 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int			ft_pass_n(char *word, int i)
{
	int	y;

	y = i;
	while (word[i])
	{
		while (word[i] && word[i] == ' ')
			i++;
		if (word[i] && word[i] == '-')
		{
			y = i;
			i++;
			while (word[i] && word[i] == 'n')
				i++;
		}
		if (word[i] != ' ')
			return (y);
	}
	return (y);
}

int			ft_echo(t_word *word)
{
	int	nl;
	int	i;

	nl = FALSE;
	i = ft_pass_n(word->data, 0);
	if (i > 0)
		nl = TRUE;
	ft_ps(&word->data[i]);
	if (nl == TRUE)
		return (0);
	ft_putstr_fd("\n", STDOUT);
	return (0);
}
