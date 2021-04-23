/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolasessayan <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 21:46:50 by nicolases         #+#    #+#             */
/*   Updated: 2021/04/23 21:46:51 by nicolases        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void		ft_reverse_parent(char *line, int *process_num, int **pfd, int pid)
{
	int		stats;

	waitpid(pid, &stats, 0);
	if (*process_num > 0 && ft_char_stop(line, *process_num - 1) == '|')
		close(pfd[*process_num - 1][0]);
	pfd[*process_num][0] = ft_fd_in_mute(line, *process_num);
	if (pfd[*process_num][0] == -1)
		*process_num = *process_num + forward_to_semi(line, *process_num);
	else
		close(pfd[*process_num][0]);
}

void		ft_reverse_back(char *line, t_data *d, int process_num, int **pfd)
{
	int		n;
	int		k;

	k = ft_backward_count(line, process_num);
	n = ft_chevron_count(line, process_num - k);
	if (n != -1)
	{
		pfd[process_num][1] = ft_fd_out(line, process_num - k + n,
			ft_char_stop(line, process_num - k + n));
		dup2(pfd[process_num][1], STDOUT);
	}
	n = ft_reverse_count(line, process_num - k);
	pfd[process_num][0] = ft_fd_in(line, process_num - k + n);
	if (pfd[process_num][0] == -1)
	{
		if (n != -1)
			close(pfd[process_num][1]);
		exit(g_status);
	}
	dup2(pfd[process_num][0], STDIN);
	ft_exec_move(line, d, process_num, k);
	close(pfd[process_num][0]);
	if (n != -1)
		close(pfd[process_num][1]);
}

void		ft_reverse(char *line, t_data *d, int *process_num, int **pfd)
{
	int		pid;
	int		n;

	pid = fork();
	if (pid == 0)
	{
		if (*process_num > 0 && ft_char_stop(line, *process_num - 1) == '|')
		{
			close(pfd[*process_num - 1][1]);
			dup2(pfd[*process_num - 1][0], 0);
		}
		pfd[*process_num][0] = ft_fd_in(line, *process_num);
		if (pfd[*process_num][0] == -1)
			exit(g_status);
		close(pfd[*process_num][0]);
		n = ft_reverse_count(line, *process_num);
		if (n == 0)
			ft_reverse_back(line, d, *process_num, pfd);
		exit(g_status);
	}
	else
		ft_reverse_parent(line, process_num, pfd, pid);
}
