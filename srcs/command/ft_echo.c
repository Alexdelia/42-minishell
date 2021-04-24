/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 17:41:22 by adelille          #+#    #+#             */
/*   Updated: 2021/04/24 13:37:50 by adelille         ###   ########.fr       */
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
	ft_ps_but_one_c(&word->data[i], ' ', STDOUT);
	if (nl == TRUE)
		return (0);
	ft_putstr_fd("\n", STDOUT);
	return (0);
}
