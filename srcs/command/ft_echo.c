/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 17:41:22 by adelille          #+#    #+#             */
/*   Updated: 2021/05/05 09:14:33 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int			ft_pass_n(char *word, int i, int *nl)
{
	int	y;

	y = i;
	while (word[i])
	{
		while (word[i] && word[i] == ' ')
			i++;
		y = i;
		if (word[i] && word[i] == '-')
		{
			i++;
			while (word[i] && word[i] == 'n')
				i++;
		}
		if (word[i] && word[i] != ' ')
			return (y);
		else if (!word[i])
		{
			*nl = TRUE;
			return (i);
		}
		else
			*nl = TRUE;
	}
	return (y);
}

int			ft_echo(t_word *word)
{
	int	nl;
	int	i;

	nl = FALSE;
	i = ft_pass_n(word->data, 0, &nl);
	ft_ps(&word->data[i]);
	if (nl == TRUE)
		return (0);
	ft_putstr_fd("\n", STDOUT);
	return (0);
}
