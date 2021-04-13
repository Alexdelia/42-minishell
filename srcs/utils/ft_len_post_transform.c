/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_len_post_transform.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 14:09:08 by adelille          #+#    #+#             */
/*   Updated: 2021/04/13 14:55:14 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	ft_len_dollar(t_parser *p, t_data *d, const char *str)
{
	char	*na_env;
	int		start;

	start = p->i;
	while (str[p->i] && str[p->i] != ' ' && str[p->i] != ';'
		&& str[p->i] != '\'' && str[p->i] != '\"' && str[p->i] != '='
		&& str[p->i] != '|' && str[p->i] != '>' && str[p->i] != '<'
		&& str[p->i] != '\\')
		p->i++;
	if (start == p->i - 1)
	{
		p->y++;
		return ;
	}
	na_env = ft_strdup2((char *)str, start + 1, p->i);
	if (ft_strcmp(na_env, "?") == 0)
		p->y += ft_nbrlen(g_status);
	else
		p->y += ft_strlen(ft_env_search(na_env, d->env));
	free(na_env);
}

static void	ft_len_double(t_parser *p, t_data *d, const char *str)
{
	int	ml;

	ml = FALSE;
	p->i++;
	while (str[p->i] && str[p->i] != '\"')
	{
		if (str[p->i] == '$')
			ft_len_dollar(p, d, str);
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
			p->i++;
			p->y++;
		}
	}
	if (!str[p->i] || ml == TRUE)
		p->i = -1;
	else
		p->i++;
}

static void	ft_len_simple(t_parser *p, const char *str)
{
	p->i++;
	while (str[p->i] && str[p->i] != '\'')
	{
		p->i++;
		p->y++;
	}
	if (!str[p->i])
		p->i = -1;
	else
		p->i++;
}

int		ft_strlen_post_transform(const char *str, t_data *d)
{
	t_parser	p;
	int			ml;
	
	p.y = 0;
	p.i = 0;
	ml = FALSE;
	while (ml == FALSE && str[p.i] && str[p.i] != ';' && str[p.i] != '|'
		&& str[p.i] != '>' && str[p.i] != '<')
	{
		if (str[p.i] == '$')
			ft_len_dollar(&p, d, str);
		else if (str[p.i] == '\"')
			ft_len_double(&p, d, str);
		else if (str[p.i] == '\'')
			ft_len_simple(&p, str);
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
			p.i++;
			p.y++;
		}
		if (p.i == -1)
			ml = TRUE;
	}
	if (ml == TRUE)
		return (-1);
	return (p.y);
}
