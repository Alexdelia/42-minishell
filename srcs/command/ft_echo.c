/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 17:41:22 by adelille          #+#    #+#             */
/*   Updated: 2021/04/20 10:10:01 by nicolases        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	ft_no_more_c(char *str, int i, char c)
{
	while (str[i])
	{
		if (str[i] != c)
			return (FALSE);
		i++;
	}
	return (TRUE);
}

static int	ft_ps_but_one_c(char *str, char c, int fd)
{
	int	is_c;
	int	i;

	i = 0;
	is_c = FALSE;
	while (str[i])
	{
		if (ft_no_more_c(str, i, c) == TRUE)
			break ;
		if (str[i] == c)
			is_c = TRUE;
		write(fd, &str[i], 1);
		if (is_c == FALSE)
			i++;
		while (is_c == TRUE)
		{
			i++;
			if (str[i] != c)
				is_c = FALSE;
		}
	}
	return (i);
}

int			ft_echo(t_word *word)
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
	ft_ps_but_one_c(&word->data[i], ' ', STDOUT);
	i = 0;
	if (word->data[0] == '-')
	{
		i++;
		while (word->data[i] && word->data[i] == 'n')
			i++;
		if (!word->data[i] || word->data[i] == ' ')
			return (0);
	}
	ft_putstr_fd("\n", STDOUT);
	return (0);
}
