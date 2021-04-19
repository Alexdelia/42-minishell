/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_char_stop.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 14:31:45 by adelille          #+#    #+#             */
/*   Updated: 2021/04/19 15:32:41 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_is_double_c(char *line, int i, char c)
{
	if (line[i] && line[i + 1] && line[i] == c && line[i + 1] == c)
		return (TRUE);
	return (FALSE);
}

char		ft_char_stop(char *line, int process_num)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == ';' || line[i] == '|' || line[i] == '>'
			|| line[i] == '<')
		{
			if (process_num == 0)
			{
				if (ft_is_double_c(line, i, '>') == TRUE)
					return ('C');
				if (ft_is_double_c(line, i, '<') == TRUE)
					return ('R');
				return (line[i]);
			}
			if (ft_is_double_c(line, i, '>') == TRUE)
				i++;
			if (ft_is_double_c(line, i, '<') == TRUE)
				i++;
			process_num--;
		}
		i++;
	}
	return ('\0');
}
