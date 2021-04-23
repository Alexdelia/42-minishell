/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_call.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolasessayan <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 18:17:39 by nicolases         #+#    #+#             */
/*   Updated: 2021/04/21 18:17:41 by nicolases        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int			ft_parse_exec(t_word *word, t_data *d)
{
	if (ft_strcmp(word->data, "echo") == 0)
		g_status = ft_echo(word->next);
	else if (ft_strcmp(word->data, "cd") == 0)
		g_status = ft_cd(word->next->data);
	else if (ft_strcmp(word->data, "pwd") == 0)
		g_status = ft_pwd();
	else if (ft_strcmp(word->data, "export") == 0)
		g_status = ft_export(word->next, &(d->env));
	else if (ft_strcmp(word->data, "unset") == 0)
		g_status = ft_unset(word->next, &(d->env));
	else if (ft_strcmp(word->data, "env") == 0)
		g_status = ft_env(d->env);
	else if (ft_strcmp(word->data, "exit") == 0)
		g_status = ft_exit(d);
	else if (word->data[0] && (word->data[0] == '.'
				|| word->data[0] == '/'))
		g_status = ft_exec(word, d->env);
	else if (ft_statable(&word, d->env) == TRUE)
		g_status = ft_exec(word, d->env);
	else if (is_included(word->data, '='))
		g_status = ft_mi_error(word->data, "in-line arg not supported", 127);
	else
		g_status = ft_mi_error(word->data, "command not found", 127);
	return (0);
}

void		ft_pipe(char *line, t_data *d, int process_num, int **pfd)
{
	int		pid;
	int		stats;

	//printf("*** FT_PIPE ***\n");//
	pipe(pfd[process_num]);
	pid = fork();
	if (pid == 0)
	{
		close(pfd[process_num][0]);
		dup2(pfd[process_num][1], 1);
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
		close(pfd[process_num][1]);
	}
}

int			ft_chevron_count(char *line, int process_num)
{
	int		n;
	int		ret;
	char	char_stop;

	char_stop = ft_char_stop(line, process_num);
	ret = -1;
	n = -1;
	while (char_stop != ';' && char_stop != '|' && char_stop != '\0')
	{
		char_stop = ft_char_stop(line, process_num);
		n++;
		if (char_stop == '>' || char_stop == 'C')
			ret = n;
		//printf("*** char_stop = %c | ret = %d ***\n", char_stop, ret);
		process_num++;
	}
	return (ret);
}

int			ft_reverse_count(char *line, int process_num)
{
	int		n;
	int		ret;
	char	char_stop;

	//printf("*** FT_REVERSE ***\n");//
	char_stop = ft_char_stop(line, process_num);
	ret = -1;
	n = -1;
	while (char_stop != ';' && char_stop != '|' && char_stop != '\0')
	{
		char_stop = ft_char_stop(line, process_num);
		n++;
		if (char_stop == '<')
			ret = n;
		//printf("*** char_stop = %c | ret = %d ***\n", char_stop, ret);
		process_num++;
	}
	return (ret);
}

int			ft_backward_count(char *line, int process_num)
{
	int		n;
	char	char_stop;

	n = -1;
	while (process_num >= 0)
	{
		char_stop = ft_char_stop(line, process_num);
		if (char_stop == '>' || char_stop == 'C' || char_stop == '<')
			n++;
		else if (char_stop == '\0' || char_stop == ';' || char_stop == '|')
			return (n);	
		process_num--;
	}
	return (n);
}

void		ft_chevron(char *line, t_data *d, int *process_num, int **pfd)
{
	int		pid;
	int		stats;
	int		fd[2];
	int		n;
	int 	k;

	printf("*** FT_CHEVRON ***\n");//
	pid = fork();
	if (pid == 0)
	{
		if (*process_num > 0 && ft_char_stop(line, *process_num - 1) == '|')
		{
			close(pfd[*process_num - 1][1]);
			dup2(pfd[*process_num - 1][0], 0);
		}
		n = ft_chevron_count(line, *process_num);
		//printf("*** CHEVRON COUNT = %d ***\n", n);
		if (n != 0)
		{
			fd[1] = ft_fd_out(line, *process_num,
				ft_char_stop(line, *process_num));
			close(fd[1]);
		}
		else
		{
			k = ft_backward_count(line, *process_num);
			//printf("*** BACKWARD COUNT = %d ***\n", k);
			n = ft_chevron_count(line, *process_num - k);
			//printf("*** INTERNAL CHEVRON COUNT = %d ***\n", n);
			fd[1] = ft_fd_out(line, *process_num - k + n,
				ft_char_stop(line, *process_num - k + n));
			n = ft_reverse_count(line, *process_num - k);
			//printf("*** INTERNAL REVERSE COUNT = %d ***\n", n);
			if (n != -1)
			{
				fd[0] = ft_fd_in(line, *process_num - k + n,
					ft_char_stop(line, *process_num - k + n));
				if (fd[0] == -1)
				{
					close(fd[1]);
					exit(g_status);
				}
				dup2(fd[0], STDIN);
			}
			dup2(fd[1], STDOUT);
			move_word(line, d, *process_num, -k);
			ft_parse_exec(d->word, d);
			move_word(line, d, *process_num, k);
			if (n != -1)
				close(fd[0]);
			close(fd[1]);
		}
		exit(g_status);
	}
	else
	{
		waitpid(pid, &stats, 0);
		if (*process_num > 0 && ft_char_stop(line, *process_num - 1) == '|')
			close(pfd[*process_num - 1][0]);
	}
}

void		ft_reverse(char *line, t_data *d, int *process_num, int **pfd)
{
	int		pid;
	int		stats;
	int		fd[2];
	int		n;
	int 	k;

	printf("*** FT_REVERSE ***\n");//
	pid = fork();
	if (pid == 0)
	{
		if (*process_num > 0 && ft_char_stop(line, *process_num - 1) == '|')
		{
			close(pfd[*process_num - 1][1]);
			dup2(pfd[*process_num - 1][0], 0);
		}
		n = ft_reverse_count(line, *process_num);
		//printf("*** REVERSE COUNT = %d ***\n", n);
		if (n != 0)
		{
			fd[0] = ft_fd_in(line, *process_num,
				ft_char_stop(line, *process_num));
			if (fd[0] == -1)
				exit(g_status);
			close(fd[0]);
		}
		else
		{
			k = ft_backward_count(line, *process_num);
			//printf("*** BACKWARD COUNT = %d ***\n", k);
			n = ft_chevron_count(line, *process_num - k);
			//printf("*** INTERNAL CHEVRON COUNT = %d ***\n", n);
			if (n != -1)
			{
				fd[1] = ft_fd_out(line, *process_num - k + n,
					ft_char_stop(line, *process_num - k + n));
				dup2(fd[1], STDOUT);
			}
			n = ft_reverse_count(line, *process_num - k);
			//printf("*** INTERNAL REVERSE COUNT = %d ***\n", n);
			fd[0] = ft_fd_in(line, *process_num - k + n,
				ft_char_stop(line, *process_num - k + n));
			if (fd[0] == -1)
			{
				if (n != -1)
					close(fd[1]);				
				exit(g_status);
			}
			dup2(fd[0], STDIN);
			move_word(line, d, *process_num, -k);
			ft_parse_exec(d->word, d);
			move_word(line, d, *process_num, k);
			close(fd[0]);
			if (n != -1)
				close(fd[1]);
		}
		exit(g_status);
	}
	else
	{
		waitpid(pid, &stats, 0);
		if (*process_num > 0 && ft_char_stop(line, *process_num - 1) == '|')
			close(pfd[*process_num - 1][0]);
	}
	//printf("*** END OF FT_REVERSE ***\n");//
}

void		ft_semi(char *line, t_data *d, int process_num, int **pfd)
{
	int		pid;
	int		stats;

	//printf("*** FT_SEMI ***\n");//
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

void		ft_exec_word(char *line, t_data *d, int *process_num, int **pfd)
{
	char		char_stop;

	printf("=========== PROCESS %d ================\n", *process_num);//
	char_stop = ft_char_stop(line, *process_num);
	//ft_print_word(d->word);//
	//printf("*** char_stop = %c ***\n", char_stop);//
	if (char_stop == ';' || char_stop == '\0')
		ft_semi(line, d, *process_num, pfd);
	else if (char_stop == '|')
		ft_pipe(line, d, *process_num, pfd);
	else if (char_stop == '>' || char_stop == 'C')
		ft_chevron(line, d, process_num, pfd);
	else if (char_stop == '<')
		ft_reverse(line, d, process_num, pfd);
}

int			redir_errone(char *line, t_data *d, int process_num, int char_stop)
{
	if (char_stop == 'R')
		return (g_status = ft_mi_error("redirection", "<< not supported", 1));
	if (char_stop == ';' && d->word->data[0] == '\0')
	{
		return (g_status = ft_mi_error("redirection",
			"syntax error near unexpected token `;'", 258));
	}
	if (char_stop == '|' && d->word->data[0] == '\0')
	{
		return (g_status = ft_mi_error("redirection",
			"syntax error near unexpected token `|'", 258));
	}
	if (char_stop == '>' || char_stop == '<')
	{
		move_word(line, d, process_num, 1);
		if (d->word->data[0] == '\0')
		{
			move_word(line, d, process_num, -1);
			return (g_status = ft_mi_error("redirection",
					"syntax error near unexpected token `newline'", 258));
		}
		move_word(line, d, process_num, -1);
	}
	if (process_num > 0 && char_stop == '\0' && d->word->data[0] == '\0'
		&& ft_char_stop(line, process_num - 1) == '|')
	{
		return (g_status = ft_mi_error("redirection",
			"Error: multiligne", 1));
	}
	return (0);
}

int			redir_errall(char *line, t_data *d, int c)
{
	int		process_num;
	char	char_stop;

	process_num = 0;
	while (process_num < c)
	{
		char_stop = ft_char_stop(line, process_num);
		if (ft_word_split(d, line, process_num) == 0)
		{
			if (redir_errone(line, d, process_num, char_stop) != 0)
			{
				ft_free_all_word(d->word);
				d->word = NULL;
				return (1);
			}
		}
		ft_free_all_word(d->word);
		d->word = NULL;
		process_num++;
	}
	return (0);
}

void		ft_exec_command(char *line, t_data *d)
{
	int		c;
	int		process_num;
	int		**pfd;

	if (!line[0])
		return ;
	c = ft_count_process(line);
	if (redir_errall(line, d, c) == 1)
		return ;
	pfd = init_pfd(c);
	process_num = 0;
	while (process_num < c)
	{
		if (ft_word_split(d, line, process_num) == 0
			&& d->word->data[0] != '\0')
			ft_exec_word(line, d, &process_num, pfd);
		ft_free_all_word(d->word);
		d->word = NULL;
		process_num++;
	}
	free_pfd(pfd, c);
}
