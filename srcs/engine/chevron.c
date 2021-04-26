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

int			check_build_fd(char *line, int process_num, int **pfd)
{
	char char_stop;

	char_stop = ft_char_stop(line, process_num);
	while (char_stop != ';' && char_stop != '!' && char_stop != '\0')
	{
		char_stop = ft_char_stop(line, process_num);
		if (char_stop == '>' || char_stop == 'C')
		{
			pfd[process_num][1] = ft_fd_out(line, process_num,
				ft_char_stop(line, process_num));
			close(pfd[process_num][1]);
		}
		else if (char_stop == '<')
		{
			pfd[process_num][0] = ft_fd_in(line, process_num);
			if (pfd[process_num][0] == -1)
				return (1);
			close(pfd[process_num][0]);
		}
		process_num++;
	}
	return (0);
}

int			determine_stdin(char *line, int process_num, int **pfd)
{
	int	n;

	(void)pfd;
	n = ft_reverse_count(line, process_num);
	printf("*** REVERSE COUNT = %d \n", n);
	if (n != -1)
		return (ft_fd_in(line, process_num + n));
	else if (n == -1 && ft_char_stop(line, process_num - 1) == '|')
		return (pfd[process_num - 1][0]);
	else if (n == -1 && ft_char_stop(line, process_num - 1) != '|')
		return (STDIN);
	else
		return (-1);
}

int			determine_stdout(char *line, int process_num, int **pfd)
{
	int	n;
	int	k;

	k = forward_to_semi(line, process_num);
	printf("*** FORWARD COUNT = %d \n", k);
	n = ft_chevron_count(line, process_num);
	printf("*** CHEVRON COUNT = %d \n", n);
	if (n != -1)
		return (ft_fd_out(line, process_num + n,
			ft_char_stop(line, process_num + n)));
	else if (n == -1 && ft_char_stop(line, process_num + k) == '|')
	{
		pipe(pfd[process_num + k]);
		return (pfd[process_num + k][1]);
	}
	else if (n == -1 && ft_char_stop(line, process_num + k) != '|')
		return (STDOUT);
	else
		return (-1);
}

void		execute_chevron(char *line, t_data *d, int *process_num, int **pfd)
{
	if (check_build_fd(line, *process_num, pfd) == 1)
	{
		*process_num = *process_num + forward_to_semi(line, *process_num);
		return ;
	}
	pfd[*process_num][0] = determine_stdin(line, *process_num, pfd);
	pfd[*process_num][1] = determine_stdout(line, *process_num, pfd);
	dup2(pfd[*process_num][0], STDIN);
	dup2(pfd[*process_num][1], STDOUT);
	ft_parse_exec(d->word, d);
	*process_num = *process_num + forward_to_semi(line, *process_num);
}

void		ft_chevron(char *line, t_data *d, int *process_num, int **pfd)
{
	int 	pid;
	int 	saved_stdout;
	int		saved_stdin;
	int		stats;

	saved_stdin = dup(STDIN);
	saved_stdout = dup(STDOUT);
	if (process_num > 0 && ft_char_stop(line, *process_num - 1) == '|')
	{
		pid = fork();
		if (pid == 0)
		{
			execute_chevron(line, d, process_num, pfd);
			close(pfd[*process_num][0]);
		}
		else
		{
			waitpid(pid, &stats, 0);
			if (stats > 255)
				g_status = stats / 256;
			else
				g_status = stats;
			close(pfd[*process_num][0]);
		}
	}
	else
	{
		execute_chevron(line, d, process_num, pfd);
		//close(pfd[*process_num][0]);
	}
	//close(pfd[*process_num][1]);
	dup2(saved_stdin, STDIN);
	dup2(saved_stdout, STDOUT);
	close(saved_stdin);
	close(saved_stdout);
}
