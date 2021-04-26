/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_error.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolasessayan <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 21:46:11 by nicolases         #+#    #+#             */
/*   Updated: 2021/04/26 11:45:07 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	ft_redir_quote(char *line, int i)
{
	if (line[i] == '\"'
			&& (!line[i - 1] || (line[i - 1] && line[i - 1] != '\\')))
	{
		i++;
		while (line[i] && (line[i] != '\"' || (line[i - 1]
				&& line[i - 1] == '\\' && line[i] == '\"')))
			i++;
		if (!line[i])
			return (-1);
	}
	else if (line[i] == '\''
			&& (!line[i - 1] || (line[i - 1] && line[i - 1] != '\\')))
	{
		i++;
		while (line[i] && (line[i] != '\'' || (line[i - 1]
				&& line[i - 1] == '\\' && line[i] == '\'')))
			i++;
		if (!line[i])
			return (-1);
	}
	return (i);
}

static int	ft_redir_char_stop(char *line, int i)
{
	if (line[i + 1] && line[i] == '>' && line[i + 1] == '>')
		i++;
	if (line[i + 1] && line[i] == '<' && line[i + 1] == '<')
		return (ft_syntax_error(line, i, 2));
	i++;
	while (line[i] && line[i] == ' ')
		i++;
	if (line[i] && (line[i] == ';' || line[i] == '|'
				|| line[i] == '>' || line[i] == '<'))
		return (ft_syntax_error(line, i, 0));
	if (!line[i])
		return (ft_syntax_error(line, i - 1, -1));
	i--;
	return (i);
}

static int	ft_redir_loop(char *line)
{
	int	ml;
	int	i;

	ml = FALSE;
	i = 0;
	while (line[i])
	{
		i = ft_redir_quote(line, i);
		if (i == -1)
			return (TRUE);
		else if (line[i] && (line[i] == ';' || line[i] == '|'
				|| line[i] == '>' || line[i] == '<')
				&& (!line[i - 1] || (line[i - 1] && line[i - 1] != '\\')))
		{
			i = ft_redir_char_stop(line, i);
			if (i == -1)
				return (-1);
		}
		i++;
	}
	return (ml);
}

int			redir_errall(char *line)
{
	int	ml;

	ml = ft_redir_loop(line);
	if (ml == TRUE)
	{
		g_status = 1;
		ft_pserc("minishell: Error: multiligne\n", RED);
		return (1);
	}
	else if (ml == -1)
		return (1);
	return (0);
}
