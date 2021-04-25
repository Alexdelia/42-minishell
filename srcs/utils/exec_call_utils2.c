/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_call_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolasessayan <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 16:03:56 by nicolases         #+#    #+#             */
/*   Updated: 2021/04/22 16:04:41 by nicolases        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int			ft_count_process(char *line)
{
	int i;
	int	process_num;

	process_num = 1;
	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '|' || line[i] == ';')
			process_num++;
		else if (line[i] == '>')
		{
			process_num++;
			if (line[i + 1] != '\0' && line[i + 1] == '>')
				i++;
		}
		else if (line[i] == '<')
		{
			process_num++;
			if (line[i + 1] != '\0' && line[i + 1] == '<')
				i++;
		}
		i++;
	}
	return (process_num);
}
