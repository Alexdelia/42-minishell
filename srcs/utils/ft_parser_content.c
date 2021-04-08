/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser_content.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 13:08:56 by adelille          #+#    #+#             */
/*   Updated: 2021/04/08 14:23:45 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	ft_conv_dollar(t_parser *p, t_env *env, char *str, char **res)
{
	p->y = ft_mi_strcat(res, &str[p->i], p->y, env);
	while (str[p->i] && str[p->i] != ' ' && str[p->i] != ';'
		&& str[p->i] != '\'' && str[p->i] != '\"' && str[p->i] != '='
		&& str[p->i] != '|' && str[p->i] != '>' && str[p->i] != '<')
		p->i++;
}

static void	ft_conv_double(t_parser *p, t_env *env, char *str, char **res)
{
	p->i++;
	while (str[p->i] && str[p->i] != '\"')
	{
		if (str[p->i] == '$')
			ft_conv_dollar(p, env, str, res);
		else
		{
			*res[p->y] = str[p->i];
			p->i++;
			p->y++;
		}
	}
	if (!str[p->i])
		p->i = -1;
}

static void	ft_conv_simple(t_parser *p, char *str, char **res)
{
	p->i++;
	while (str[p->i] && str[p->i] != '\'')
	{
		*res[p->y] = str[p->i];
		p->i++;
		p->y++;
	}
	if (!str[p->i])
		p->i = -1;
}

int			ft_content(t_word **word, t_env *env, char *str, int i)
{
	t_parser	p;
	char		*res;
	int			ml;

	res = (char *)malloc(sizeof(*res) * (ft_strlen(str) + PATH_LEN));
	p.y = 0;
	p.i = i;
	ml = FALSE;
	while (str[p.i] && str[p.i] != ';' && str[p.i] != '|'
		&& str[p.i] != '>' && str[p.i] != '<')
	{
		if (str[p.i] == '$')
			ft_conv_dollar(&p, env, str, &res);
		else if (str[p.i] == '\"')
			ft_conv_double(&p, env, str, &res);
		else if (str[p.i] == '\'')
			ft_conv_simple(&p, str, &res);
		else
		{
			if (str[p.i] == '\\')
			{
				p.i++;
				if (!str[p.i])
				{
					ml = TRUE;
					break;
				}
			}
			res[p.y] = str[p.i];
			p.i++;
			p.y++;
		}
	}
	res[p.i] = '\0';
	ft_add_back_word(word, ft_new_word(res));
	free(res);
	if (ml == TRUE)
		return (-1);
	return (p.i);
}