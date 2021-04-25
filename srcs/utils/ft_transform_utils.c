/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_transform_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 15:29:24 by adelille          #+#    #+#             */
/*   Updated: 2021/04/13 15:51:05 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		ft_len_inner_trans(t_parser *p, const char *str, int ml)
{
	if (str[p->i] == '\\')
	{
		p->i++;
		if (!str[p->i])
			return (TRUE);
	}
	p->i++;
	p->y++;
	return (ml);
}

int		ft_inner_trans(t_parser *p, const char *str, char **res, int ml)
{
	if (str[p->i] == '\\')
	{
		p->i++;
		if (!str[p->i])
			return (TRUE);
	}
	(*res)[p->y] = str[p->i];
	p->i++;
	p->y++;
	return (ml);
}

void	ft_loop_trans(t_parser *p, t_data *d, const char *str, char *res)
{
	while (str[p->i] && str[p->i] != ';' && str[p->i] != '|'
		&& str[p->i] != '>' && str[p->i] != '<')
	{
		if (str[p->i] == '$')
			ft_conv_dollar(p, d, str, &res);
		else if (str[p->i] == '\"')
			ft_conv_double(p, d, str, &res);
		else if (str[p->i] == '\'')
			ft_conv_simple(p, str, res);
		else
		{
			if (str[p->i] == '\\')
			{
				p->i++;
				if (!str[p->i])
					break ;
			}
			res[p->y] = str[p->i];
			p->i++;
			p->y++;
		}
	}
	res[p->y] = '\0';
}
