/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolasessayan <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 21:46:31 by nicolases         #+#    #+#             */
/*   Updated: 2021/04/23 22:36:07 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void		ft_pipe_parent(char *line, int process_num, int **pfd, int pid)
{
	int		stats;

	(void)line;
	waitpid(pid, &stats, 0);
	if (stats > 255)
		g_status = stats / 256;
	else
		g_status = stats;
	close(pfd[process_num][1]);
}

void		ft_pipe(char *line, t_data *d, int process_num, int **pfd)
{
	int		pid;

	if (process_num == 0 || (ft_char_stop(line, process_num - 1) != '>'
		&& ft_char_stop(line, process_num - 1) != 'C'
		&& ft_char_stop(line, process_num - 1) != '<'))
		pipe(pfd[process_num]);
	pid = fork();
	if (pid == 0)
	{
		if (process_num == 0 || (ft_char_stop(line, process_num - 1) != '>'
			&& ft_char_stop(line, process_num - 1) != 'C'
			&& ft_char_stop(line, process_num - 1) != '<'))
			dup2(pfd[process_num][1], STDOUT);
		if (process_num > 0 && ft_char_stop(line, process_num - 1) == '|')
			dup2(pfd[process_num - 1][0], STDIN);
		if (process_num == 0 || (ft_char_stop(line, process_num - 1) != '>'
			&& ft_char_stop(line, process_num - 1) != 'C'
			&& ft_char_stop(line, process_num - 1) != '<'))
			ft_parse_exec(d->word, d);
		exit(g_status);
	}
	else
		ft_pipe_parent(line, process_num, pfd, pid);
}
