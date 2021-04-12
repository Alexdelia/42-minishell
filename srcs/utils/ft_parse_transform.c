/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_transform.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 13:08:56 by adelille          #+#    #+#             */
/*   Updated: 2021/04/12 15:04:01 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	ft_conv_dollar(t_parser *p, t_data *d, char *str, char **res)
{
	p->y = ft_mi_strcat(res, &str[p->i], p->y, d);
	while (str[p->i] && str[p->i] != ' ' && str[p->i] != ';'
		&& str[p->i] != '\'' && str[p->i] != '\"' && str[p->i] != '='
		&& str[p->i] != '|' && str[p->i] != '>' && str[p->i] != '<'
		&& str[p->i] != '\\')
		p->i++;
}

static void	ft_conv_double(t_parser *p, t_data *d, char *str, char **res)
{
	int	ml;

	ml = FALSE;
	p->i++;
	while (str[p->i] && str[p->i] != '\"')
	{
		if (str[p->i] == '$')
			ft_conv_dollar(p, d, str, res);
		else
		{
			if (str[p->i] == '\\')
			{
				p->i++;
				if (!str[p->i])
				{
					ml = TRUE;
					break;
				}
			}
			(*res)[p->y] = str[p->i];
			p->i++;
			p->y++;
		}
	}
	if (!str[p->i] || ml == TRUE)
		p->i = -1;
	else
		p->i++;
}

static void	ft_conv_simple(t_parser *p, char *str, char **res)
{
	p->i++;
	while (str[p->i] && str[p->i] != '\'')
	{
		(*res)[p->y] = str[p->i];
		p->i++;
		p->y++;
	}
	if (!str[p->i])
		p->i = -1;
	else
		p->i++;
}

int			ft_transform(t_data *d, char *str, int first)
{
	t_parser	p;
	char		*res;
	int			len;
	
	len = ft_strlen_post_transform(str, d);
	if (len < 0)
		return (-1);
	res = (char *)malloc(sizeof(*res) * (len + 1));
	p.y = 0;
	p.i = 0;
	while (str[p.i] && str[p.i] != ';' && str[p.i] != '|'
		&& str[p.i] != '>' && str[p.i] != '<')
	{
		if (str[p.i] == '$')
			ft_conv_dollar(&p, d, str, &res);
		else if (str[p.i] == '\"')
			ft_conv_double(&p, d, str, &res);
		else if (str[p.i] == '\'')
			ft_conv_simple(&p, str, &res);
		else
		{
			if (str[p.i] == '\\')
			{
				p.i++;
				if (!str[p.i])
					break;
			}
			res[p.y] = str[p.i];
			p.i++;
			p.y++;
		}
	}
	res[p.i] = '\0';
	if (first == TRUE)
		d->word = ft_new_word(res);
	else
		ft_add_back_word(&(d->word), ft_new_word(res));
	free(res);
	return (p.i);
}
