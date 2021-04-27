/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolasessayan <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 21:47:06 by nicolases         #+#    #+#             */
/*   Updated: 2021/04/25 14:32:57 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void		ft_semi(char *line, t_data *d, int process_num, int **pfd)
{
	int		saved_stdin;

	saved_stdin = dup(STDIN);
	if (process_num > 0 && ft_char_stop(line, process_num - 1) == '|')
		dup2(pfd[process_num - 1][0], STDIN);
	if (process_num == 0 || (ft_char_stop(line, process_num - 1) != '>'
			&& ft_char_stop(line, process_num - 1) != 'C'
			&& ft_char_stop(line, process_num - 1) != '<'))
	{
		ft_parse_exec(d->word, d);
	}
	if (process_num > 0 && ft_char_stop(line, process_num - 1) == '|')
		dup2(saved_stdin, STDIN);
}
