/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_word_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 06:51:14 by adelille          #+#    #+#             */
/*   Updated: 2021/03/31 07:43:05 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_convert_string(t_word **word, char *str, int i)
{
	int		y;
	char	*elem

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
	ft_add_back_word(word, ft_new_word(elem));
	free(elem);
	return (i);
}

static int	ft_convert_basic(t_word **, char *str, int i)
{
	int		y;
	char	*elem

	y = 0;
	i++;
	while (str[i] && str[i + y] != ' ')
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
	ft_add_back_word(word, ft_new_word(elem));
	free(elem);
	return (i);
}

t_word		*ft_word_split(char const *str, int	stop)
{
	t_word	*word;
	int		i;
	int		count;

	i = 0;
	cound = 0;
	while (str[i] || stop >= 0)
	{
		if (str[i] == '|' str[i] == ';'
					|| str[i] == '>' || str[i] == '<')
		{
			if (str[i + 1] && (str[i + 1] == '>' || str[i + 1] == '<')
				i++;
			stop--;
		}
		else if (stop == 0 && str[i] == '\"' || str[i] == '\'')
			i = ft_convert_string(&word, str, i);
		else if (stop == 0)
			i = ft_convert_basic(&word, str, i);
		i++;
	}
	return (word);
}
