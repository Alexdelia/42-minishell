/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolasessayan <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 21:47:06 by nicolases         #+#    #+#             */
/*   Updated: 2021/04/23 21:47:09 by nicolases        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void		ft_semi(char *line, t_data *d, int process_num, int **pfd)
{
	int		pid;
	int		stats;

	pid = fork();
	if (pid == 0)
	{
		if (process_num > 0 && ft_char_stop(line, process_num - 1) == '|')
		{
			close(pfd[process_num - 1][1]);
			dup2(pfd[process_num - 1][0], 0);
		}
		if (process_num == 0 || (ft_char_stop(line, process_num - 1) != '>'
			&& ft_char_stop(line, process_num - 1) != 'C'
			&& ft_char_stop(line, process_num - 1) != '<'))
			ft_parse_exec(d->word, d);
		exit(g_status);
	}
	else
	{
		waitpid(pid, &stats, 0);
		if (process_num > 0 && ft_char_stop(line, process_num - 1) == '|')
			close(pfd[process_num - 1][0]);
	}
}
