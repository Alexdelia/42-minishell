/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_word_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 06:51:14 by adelille          #+#    #+#             */
/*   Updated: 2021/04/07 14:42:16 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	ft_convert_single(t_word **word, char *str, int i, int c)
{
	int		y;
	char	*elem;

	y = 0;
	i++;
	while (str[i] && str[i + y] != '\'')
		y++;
	elem = (char *)malloc(sizeof(char *) * y + 1);
	y = 0;
	while (str[i] && str[i] != '\'')
	{
		elem[y] = str[i];
		y++;
		i++;
	}
	elem[y] = '\0';
	if (c == 0)
		(*word) = ft_new_word(elem);
	else
		ft_add_back_word(word, ft_new_word(elem));
	free(elem);
	return (i);
}

static int	ft_convert_double(t_word **word, t_env *env,
		char *str, int i, int c)
{
	int		y;
	char	*elem;

	y = 0;
	i++;
	while (str[i] && str[i + y] != '\"')
		y++;
	elem = (char *)malloc(sizeof(char *) * y + 1);
	y = 0;
	while (str[i] && str[i] != '\"')
	{	
		if (str[i] == '$')
		{
			y = ft_mi_strcat(&elem, &str[i], y, env);
			while (str[i] && str[i] != '\"')
				i++;
		}
		else
		{
			elem[y] = str[i];
			y++;
			i++;
		}
	}
	elem[y] = '\0';
	if (c == 0)
		(*word) = ft_new_word(elem);
	else
		ft_add_back_word(word, ft_new_word(elem));
	free(elem);
	return (i);
}

static int	ft_convert_basic(t_word **word, t_env *env,
		char *str, int i, int c)
{
	int		y;
	char	*elem;

	y = 0;
	while (str[i + y] && str[i + y] != ' '
			&& str[i + y] != '\"' && str[i + y] != '\'')
		y++;
	elem = (char *)malloc(sizeof(char *) * (y + PATH_LEN));
	y = 0;
	while (str[i] && str[i] != ' '
			&& str[i] != '\"' && str[i] != '\'')
	{
		if (str[i] == '\\' && str[i + 1])
			i++;
		else if (str[i] == '\\' && !str[i + 1])
			return (-1);
		if (str[i] == '$')
		{
			y = ft_mi_strcat(&elem, &str[i], y, env);
			while (str[i] && str[i] != ' ' && str[i] != '\"' && str[i] != '\'')
				i++;
			break;
		}
		elem[y] = str[i];
		y++;
		i++;
	}
	elem[y] = '\0';
	if (c == 0)
		(*word) = ft_new_word(elem);
	else
		ft_add_back_word(word, ft_new_word(elem));
	free(elem);
	return (i);
}

t_word	*ft_word_split(t_env *env, char *str, int stop)
{
	int		i;
	t_word	*word;
	int		c;

	i = 0;
	c = 0;
	while (i >= 0 && str[i] && stop >= 0)
	{
		if (i > 0 && str[i] == ' ')
			i++;
		if (str[i] == '|' || str[i] == ';'
				|| str[i] == '>' || str[i] == '<')
		{
			if (str[i + 1] && (str[i + 1] == '>' || str[i + 1] == '<'))
				i++;
			stop--;
		}
		else if (stop == 0 && str[i] == '\"')
			i = ft_convert_double(&word, env, str, i, c);
		else if (stop == 0 && str[i] == '\'')
			i = ft_convert_single(&word, str, i, c);
		else if (stop == 0)
			i = ft_convert_basic(&word, env, str, i, c);
		c++;
	}
	if (i < 0)
	{
		ft_pserc("Error: multiligne\n", RED);
		ft_free_all_word(word);
		return (NULL);
	}
	return (word);
}
