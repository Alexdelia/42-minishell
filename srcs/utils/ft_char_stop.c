/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_char_stop.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 14:31:45 by adelille          #+#    #+#             */
/*   Updated: 2021/04/19 15:28:39 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	ft_char_stop(char *line, int process_num)
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
				if (line[i] && line[i + 1] && line[i] == '>'
						&& line[i + 1] == '>')
					return ('C');
				if (line[i] && line[i + 1] && line[i] == '<'
						&& line[i + 1] == '<')
					return ('R');
				return (line[i]);
			}
			if (line[i] && line[i + 1] && line[i] == '>'
					&& line[i + 1] == '>')
				i++;
			if (line[i] && line[i + 1] && line[i] == '<'
					&& line[i + 1] == '<')
				i++;
			process_num--;
		}
		i++;
	}
	return ('\0');
}
