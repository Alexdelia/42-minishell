/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_process.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 14:22:30 by adelille          #+#    #+#             */
/*   Updated: 2021/04/26 11:22:29 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int			ft_count_process(char *line)
{
	int	process_num;
	int	in;

	in = 0;
	process_num = 0;
	while (ft_char_stop(line, process_num) != '\0')
	{
		in = 1;
		process_num++;
	}
	if (process_num == 0)
		return (1);
	return (process_num + in);
}
