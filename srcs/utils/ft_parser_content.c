/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser_content.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 13:08:56 by adelille          #+#    #+#             */
/*   Updated: 2021/04/08 13:53:06 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	ft_conv_dollar(t_parser **p, t_env *env, char *str, char **res)
{
	p->y = ft_mi_strcat(res, &str[p->i], p->y, env);
	while (str[p->i] && str[p->i] != ' ' && str[p->i] != ';'
		&& str[p->i] != '\'' && str[p->i] != '\"' && str[p->i] != '='
		&& str[p->i] != '|' && str[p->i] != '>' && str[p->i] != '<')
		p->i++;
}

static void	ft_conv_double(t_parser **p, t_env *env, char *str, char **res)
{
	p->i++;
	while (str[p->i] && str[p->i] != '\"')
	{
		if (str[p->i] == '$')
			ft_conv_dollar(p, env, str, res);
		else
		{
			res[p->y] = str[p->i];
			p->i++;
			p->y++;
		}
	}
	if (!str[p->i])
		p->i = -1;
}

static void	ft_conv_simple(t_parser **p, char *str, char **res)
{
	p->i++;
	while (str[p->i] && str[p->i] != '\'')
	{
		res[p->y] = str[p->i];
		p->i++;
		p->y++;
	}
	if (!str[p->i])
		p->i = -1;
}

int			ft_content(t_word **word, t_env *env, char *str, int i);
{
	t_parser	*p;
	char		*res;

	res = (char *)malloc(sizeof(*res) * (ft_strlen(str) + PATH_LEN));
	p.y = 0;
	p.i = 0;
	while (str[p.i] && str[p.i] != ';' && str[p.i] != '|'
		&& str[p.i] != '>' && str[p.i] != '<')
	{
		if (str[p.i] == '$')
			ft_conv_dollar(&p, env, str, &res);
		else if (str[p.i] == '\"')
			ft_conv_double_quote(&p, env, str, &res);
		else if (str[p.i] == '\'')
			ft_conv_simple_quote(&p, str, &res);
		else if (str[p.i] == '\\' && str[p.i + 1])
			p.i++;
		else if (str[p.i] == '\\' && !str[p.i + 1])
			break;
		else
		{
			res[p.y] = str[p.i];
			p.i++;
			p.y++;
		}
	}
	res[p.i] = '\0';
	(*word) = ft_word_add_back(word, res);
	free(res);
	if (str[p.i] == '\\' && !str[p.i + 1])
		return (-1);
	return (p.i);
}
