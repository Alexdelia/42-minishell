/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 13:10:45 by adelille          #+#    #+#             */
/*   Updated: 2021/04/08 13:57:44 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int		ft_cmd_double(t_word **word, t_env *env, char *str, int i)
{
	char	*res;
	int		y;

	res = (char *)malloc(sizeof(*res) * (ft_strlen(str) + PATH_LEN));
	y = 0;
	while (str[i] && str[i] != '\"')
	{
		if (str[i] == '$')
		{
			y = ft_mi_strcat(&res, &str[i], y, env);
			while (str[i] && str[i] != ' ' && str[i] != '=')
				i++;
		}
		res[y] = str[i];
		i++;
		y++;
	}
	res[i] = '\0';
	(*word) = ft_new_word(res);
	free(res);
	if (str[i] != '\"')
		return (-1);
	return (i + 1);
}

static int		ft_cmd_quote(t_word **word, t_env *env, char *str, int i)
{
	char	*res;
	int		y;

	if (str[i] == '\"')
		return (ft_cmd_double(word, env, str, i));
	res = (char *)malloc(sizeof(*res) * (ft_strlen(str) + 1));
	y = 0;
	while (str[i] && str[i] != '\'')
	{
		res[y] = str[i];
		i++;
		y++;
	}
	res[i] = '\0';
	(*word) = ft_new_word(res);
	free(res);
	if (str[i] != '\'')
		return (-1);
	return (i + 1);
}

int				ft_cmd(t_word **word, t_env *env, char *str, int i)
{
	char	*res;
	int		y;

	if (str[i] == '\'' || str[i] == '\"')
		return (ft_cmd_quote(word, env, str, i));
	res = (char *)malloc(sizeof(*res) * (ft_strlen(str) + PATH_LEN));
	y = 0;
	while (str[i] && str[i] != ' ' && str[i] != ';' && str[i] != '|'
			&& str[i] != '>' && str[i] != '<')
	{
		if (str[i] == '$')
		{
			y = ft_mi_strcat(&res, &str[i], y, env);
			while (str[i] && str[i] != ' ' && str[i] != '=')
				i++;
		}
		res[y] = str[i];
		i++;
		y++;
	}
	res[i] = '\0';
	(*word) = ft_new_word(res);
	free(res);
	return (i);
}
