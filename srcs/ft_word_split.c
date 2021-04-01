/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_word_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 06:51:14 by adelille          #+#    #+#             */
/*   Updated: 2021/04/01 09:27:16 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	ft_convert_string(t_word **word, char *str, int i, int c)
{
	int		y;
	char	*elem;

	y = 0;
	i++;
	while (str[i] && (str[i + y] != '\"' || str[i + y] != '\''))
		y++;
	elem = (char *)malloc(sizeof(char *) * y + 1);
	y = 0;
	while (str[i] && (str[i] != '\"' || str[i] != '\''))
	{
		elem[y] = str[i];
		i++;
		y++;
	}
	elem[y] = '\0';
	if (c == 0)
		(*word) = ft_new_word(elem);
	else
		ft_add_back_word(word, ft_new_word(elem));
	free(elem);
	return (i);
}

static int	ft_convert_basic(t_word **word, char *str, int i, int c)
{
	int		y;
	char	*elem;

	y = 0;
	//i++;
	while (str[i + y] && str[i + y] != ' ')
		y++;
	elem = (char *)malloc(sizeof(char *) * y + 1);
	y = 0;
	while (str[i] && str[i] != ' ')
	{
		elem[y] = str[i];
		i++;
		y++;
	}
	elem[y] = '\0';
	if (c == 0)
		(*word) = ft_new_word(elem);
	else
		ft_add_back_word(word, ft_new_word(elem));
	free(elem);
	return (i);
}

t_word	*ft_word_split(char *str, int stop)
{
	int		i;
	t_word	*word;
	int		c;

	i = 0;
	c = 0;
	while (str[i] && stop >= 0)
	{
		if (i > 0)
			i++;
		if (str[i] == '|' || str[i] == ';'
					|| str[i] == '>' || str[i] == '<')
		{
			if (str[i + 1] && (str[i + 1] == '>' || str[i + 1] == '<'))
				i++;
			stop--;
		}
		else if (stop == 0 && (str[i] == '\"' || str[i] == '\''))
			i = ft_convert_string(&word, str, i, c);
		else if (stop == 0)
			i = ft_convert_basic(&word, str, i, c);
		c++;
	}
	return (word);
}
