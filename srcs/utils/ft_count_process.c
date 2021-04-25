/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_process.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 14:22:30 by adelille          #+#    #+#             */
/*   Updated: 2021/04/25 14:25:44 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int			ft_count_process(char *line)
{
	int	process_num;

	process_num = 1;
	while (ft_char_stop(line, process_num) != '\0')
		process_num++;
	return (process_num + 1);
}
