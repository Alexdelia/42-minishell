/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_char_stop.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 14:19:55 by adelille          #+#    #+#             */
/*   Updated: 2021/04/27 14:46:10 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	ft_is_double_c(char *line, int i, char c)
{
	if (line[i] && line[i + 1] && line[i] == c && line[i + 1] == c)
		return (TRUE);
	return (FALSE);
}

int			ft_char_quote(char *line, int i)
{
	if (line[i] == '\"'
		&& (i == 0 || (line[i - 1] && line[i - 1] != '\\')))
	{
		i++;
		while (line[i] && (line[i] != '\"' || (line[i - 1]
						&& line[i - 1] == '\\' && line[i] == '\"')))
			i++;
	}
	else if (line[i] == '\''
		&& (i == 0 || (line[i - 1] && line[i - 1] != '\\')))
	{
		i++;
		while (line[i] && (line[i] != '\'' || (line[i - 1]
						&& line[i - 1] == '\\' && line[i] == '\'')))
			i++;
	}
	else
		return (-1);
	return (i);
}

static char	ft_char_return(char *line, int i)
{
	if (ft_is_double_c(line, i, '>') == TRUE)
		return ('C');
	if (ft_is_double_c(line, i, '<') == TRUE)
		return ('R');
	return (line[i]);
}

char		ft_char_stop(char *line, int process_num)
{
	int	i;
	int	quote;

	i = 0;
	while (line[i])
	{
		quote = ft_char_quote(line, i);
		if (quote != -1)
			i = quote;
		else if (line[i] && (line[i] == ';' || line[i] == '|'
					|| line[i] == '>' || line[i] == '<')
				&& (!line[i - 1] || (line[i - 1] && line[i - 1] != '\\')))
		{
			if (process_num == 0)
				return (ft_char_return(line, i));
			if (ft_is_double_c(line, i, '>') == TRUE
					|| ft_is_double_c(line, i, '<') == TRUE)
				i++;
			process_num--;
		}
		if (line[i])
			i++;
	}
	return ('\0');
}
