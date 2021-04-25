/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_transform.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 13:08:56 by adelille          #+#    #+#             */
/*   Updated: 2021/04/23 23:09:44 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void		ft_conv_dollar(t_parser *p, t_data *d, const char *str, char **res)
{
	p->y = ft_mi_strcat(res, &str[p->i], p->y, d);
	while (str[p->i] && str[p->i] != ' ' && str[p->i] != ';'
		&& str[p->i] != '\'' && str[p->i] != '\"' && str[p->i] != '='
		&& str[p->i] != '|' && str[p->i] != '>' && str[p->i] != '<'
		&& str[p->i] != '\\')
		p->i++;
}

void		ft_conv_double(t_parser *p, t_data *d, const char *str, char **res)
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
			ml = ft_inner_trans(p, str, res, ml);
			if (ml == TRUE)
				break ;
		}
	}
	if (!str[p->i] || ml == TRUE)
		p->i = -1;
	else
		p->i++;
}

void		ft_conv_simple(t_parser *p, const char *str, char *res)
{
	p->i++;
	while (str[p->i] && str[p->i] != '\'')
	{
		res[p->y] = str[p->i];
		p->i++;
		p->y++;
	}
	p->i++;
}

char		*ft_tild(t_data *d, char *res)
{
	if (ft_strcmp(res, "~") == 0)
		return (ft_env_search("HOME", d->env));
	return (res);
}

int			ft_transform(t_data *d, char *str, int first)
{
	t_parser	p;
	char		*res;
	int			len;

	len = ft_strlen_post_transform(str, d, FALSE);
	if (len < 0)
		return (-1);
	res = malloc(sizeof(*res) * (len + 1));
	p.y = 0;
	p.i = 0;
	ft_loop_trans(&p, d, str, res);
	if (first == TRUE)
		d->word = ft_new_word(ft_tild(d, res));
	else
		ft_add_back_word(&(d->word), ft_new_word(ft_tild(d, res)));
	free(res);
	return (p.i);
}
