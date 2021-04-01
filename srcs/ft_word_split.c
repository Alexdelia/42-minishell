/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_word_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 06:51:14 by adelille          #+#    #+#             */
/*   Updated: 2021/04/01 08:24:25 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	ft_convert_string(t_word **word, char *str, int i, int c)
{
	int		y;
	char	*elem;

	y = 0;
	i++;
	//ft_ps("AYAYA");
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
	//t_word	*last;

	y = 0;
	//i++;
	//ft_ps("NON\n");
	while (str[i + y] && str[i + y] != ' ')
		y++;
	elem = (char *)malloc(sizeof(char *) * y + 1);
	y = 0;
	while (str[i] && str[i] != ' ')
	{
		write(1, &str[i], 1);
		elem[y] = str[i];
		i++;
		y++;
	}
	elem[y] = '\0';
	//ft_ps(elem);
	if (c == 0)
		(*word) = ft_new_word(elem);
	else
		ft_add_back_word(word, ft_new_word(elem));
	//last = ft_get_last_word(*word);
	//ft_ps(last->data);
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
	//ft_ps(ft_itoa(stop));
	while (str[i] && stop >= 0)
	{
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
		i++;
		c++;
	}
	//ft_ps("\n");
	//ft_ps(str);
	return (word);
}
