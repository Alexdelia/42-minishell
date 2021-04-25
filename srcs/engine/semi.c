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

static void	ft_end_semi(char *line, t_data *d, int process_num, int **pfd)
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

void		ft_semi(char *line, t_data *d, int process_num, int **pfd)
{
	int		pid;
	int		stats;

	pid = fork();
	if (pid == 0)
		ft_end_semi(line, d, process_num, pfd);
	else
	{
		waitpid(pid, &stats, 0);
		if (stats > 255)
			g_status = stats / 256;
		else
			g_status = stats;
		if (process_num > 0 && ft_char_stop(line, process_num - 1) == '|')
			close(pfd[process_num - 1][0]);
	}
}
