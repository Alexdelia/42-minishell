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

int			determine_stdin(char *line, int process_num, int **pfd)
{
	int	n;

	n = ft_reverse_count(line, process_num);
	if (n != -1 && ft_char_stop(line, process_num - 1) == '|')
	{
		close(pfd[process_num - 1][0]);
		return (ft_fd_in(line, process_num + n));
	}
	else if (n != -1 && ft_char_stop(line, process_num - 1) != '|')
		return (ft_fd_in(line, process_num + n));
	else if (n == -1 && ft_char_stop(line, process_num - 1) == '|')
		return (pfd[process_num - 1][0]);
	else
		return (STDIN);
}

int			determine_stdout(char *line, int process_num, int **pfd)
{
	int	n;
	int	k;

	k = forward_to_semi(line, process_num);
	n = ft_chevron_count(line, process_num);
	if (n != -1 && ft_char_stop(line, process_num + k) == '|')
	{
		pipe(pfd[process_num + k]);
		close(pfd[process_num + k][1]);
		return (ft_fd_out(line, process_num + n,
			ft_char_stop(line, process_num + n)));
	}
	else if (n != -1 && ft_char_stop(line, process_num + k) != '|')
	{
		return (ft_fd_out(line, process_num + n,
			ft_char_stop(line, process_num + n)));
	}
	else if (n == -1 && ft_char_stop(line, process_num + k) == '|')
	{
		pipe(pfd[process_num + k]);
		return (pfd[process_num + k][1]);
	}
	else
		return (STDOUT);
}

void		chevron_parent(char *line, int process_num, int **pfd, int pid)
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

void		chevron_exec(char *line, t_data *d, int *process_num, int **pfd)
{
	int		pid;
	int		n;
	int		k;

	k = forward_to_semi(line, *process_num);
	n = ft_chevron_count(line, *process_num);
	if (n == -1 && ft_char_stop(line, *process_num + k) == '|')
	{
		pid = fork();
		if (pid == 0)
		{
			ft_parse_exec(d->word, d);
			close(pfd[*process_num + k][1]);
			exit(g_status);
		}
		else
			chevron_parent(line, *process_num, pfd, pid);
	}
	else
		ft_parse_exec(d->word, d);
}

void		ft_chevron(char *line, t_data *d, int *process_num, int **pfd)
{
	int		saved_stdout;
	int		saved_stdin;
	int		k;

	k = forward_to_semi(line, *process_num);
	if (check_build_fd(line, *process_num, pfd) == 1)
	{
		if (ft_char_stop(line, *process_num + k) == '|')
		{
			pipe(pfd[*process_num + k]);
			close(pfd[*process_num + k][1]);
		}
		*process_num = *process_num + forward_to_semi(line, *process_num);
		return ;
	}
	saved_stdin = dup(STDIN);
	saved_stdout = dup(STDOUT);
	pfd[*process_num][0] = determine_stdin(line, *process_num, pfd);
	pfd[*process_num][1] = determine_stdout(line, *process_num, pfd);
	dup2(pfd[*process_num][0], STDIN);
	dup2(pfd[*process_num][1], STDOUT);
	chevron_exec(line, d, process_num, pfd);
	*process_num = *process_num + forward_to_semi(line, *process_num);
	dup2(saved_stdin, STDIN);
	dup2(saved_stdout, STDOUT);
}
