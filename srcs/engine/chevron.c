/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chevron.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolasessayan <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 21:46:41 by nicolases         #+#    #+#             */
/*   Updated: 2021/04/23 22:36:42 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void		ft_chevron_back(char *line, t_data *d, int process_num, int **pfd)
{
	int		k;
	int		n;

	k = ft_backward_count(line, process_num);
	n = ft_chevron_count(line, process_num - k);
	pfd[process_num][1] = ft_fd_out(line, process_num - k + n,
		ft_char_stop(line, process_num - k + n));
	n = ft_reverse_count(line, process_num - k);
	if (n != -1)
	{
		pfd[process_num][0] = ft_fd_in(line, process_num - k + n);
		if (pfd[process_num][0] == -1)
		{
			close(pfd[process_num][1]);
			return ;
		}
		dup2(pfd[process_num][0], STDIN);
	}
	dup2(pfd[process_num][1], STDOUT);
	ft_exec_move(line, d, process_num, k);
	if (n != -1)
		close(pfd[process_num][0]);
	close(pfd[process_num][1]);
}

void		ft_chevron_parent(int process_num, int pid, int **pfd)
{
	int		stats;

	waitpid(pid, &stats, 0);
	if (stats > 255)
		g_status = stats / 256;
	else
		g_status = stats;
	close(pfd[process_num - 1][0]);
}

void		ft_chevron_pipe(char *line, t_data *d, int process_num, int **pfd)
{
	int		pid;

	pid = fork();
	if (pid == 0)
	{
		close(pfd[process_num - 1][1]);
		dup2(pfd[process_num - 1][0], 0);
		pfd[process_num][1] = ft_fd_out(line, process_num,
			ft_char_stop(line, process_num));
		close(pfd[process_num][1]);
		if (ft_chevron_count(line, process_num) == 0)
			ft_chevron_back(line, d, process_num, pfd);
		exit(g_status);
	}
	else
		ft_chevron_parent(process_num, pid, pfd);
}

void		ft_chevron(char *line, t_data *d, int process_num, int **pfd)
{
	int saved_stdout;
	int	saved_stdin;

	saved_stdin = dup(STDIN);
	saved_stdout = dup(STDOUT);
	if (process_num > 0 && ft_char_stop(line, process_num - 1) == '|')
		ft_chevron_pipe(line, d, process_num, pfd);
	else
	{
		pfd[process_num][1] = ft_fd_out(line, process_num,
			ft_char_stop(line, process_num));
		close(pfd[process_num][1]);
		if (ft_chevron_count(line, process_num) == 0)
			ft_chevron_back(line, d, process_num, pfd);
	}
	dup2(saved_stdin, STDIN);
	dup2(saved_stdout, STDOUT);
	close(saved_stdin);
	close(saved_stdout);
}
