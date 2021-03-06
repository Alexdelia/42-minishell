/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_syntax_error.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 11:56:34 by adelille          #+#    #+#             */
/*   Updated: 2021/04/27 15:33:45 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	ft_syntax_message(char *type)
{
	g_status = 2;
	ft_pserc("minishell: redirection: syntax error near unexpected token ",
		RED);
	ft_pserc(type, RED);
	return (-1);
}

int			ft_syntax_error(char *line, int i, int way)
{
	if (way == 1)
	{
		g_status = 0;
		return (ft_mi_error("redirection", "<< not supported", -1));
	}
	else if (way == -2)
	{
		while (line[i] && line[i] != ';' && line[i] != '|'
				&& line[i] != '>' && line[i] != '<')
			i--;
		if (!line[i])
			return (ft_mi_error("redirection", "empty line", -1));
	}
	if (line[i] && line[i] == ';' && (i == 0 || line[i - 1] != '\\'))
		return (ft_syntax_message("`;'\n"));
	else if (line[i] && line[i] == ';')
		return (i);
	else if (line[i] && line[i] == '|')
		return (ft_syntax_message("`|'\n"));
	else if (line[i] && (line[i] == '>' || line[i] == '<'))
		return (ft_syntax_message("`newline'\n"));
	return (-1);
}
