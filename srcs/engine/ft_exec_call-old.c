/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_call.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 09:49:19 by adelille          #+#    #+#             */
/*   Updated: 2021/04/21 18:16:11 by nicolases        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		ft_parse_exec(t_word *word, t_data *d)
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

int		ft_count_process(char *line)
{
	int i;
	int	process_num;

	process_num = 1;
	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '|' || line[i] == ';')
			process_num++;
		else if (line[i] == '>')
		{
			process_num++;
			if (line[i + 1] != '\0' && line[i + 1] == '>')
				i++;
		}
		else if (line[i] == '<')
		{
			process_num++;
			if (line[i + 1] != '\0' && line[i + 1] == '<')
				i++;
		}
		i++;
	}
	return (process_num);
}

void	ft_pipe_process(char *line, t_data *d, int process_num, int n)
{
	int		pid[n];
	int		pfd[n - 1][2];
	int		stats;
	int		i;
	int		fd[2];
	char	char_stop;
	int		k;

	ft_free_all_word(d->word);
	d->word = NULL;
	i = 0;
	while (i < n)
	{
		pipe(pfd[i]);
		pid[i] = fork();
		if (pid[i] == 0)
		{
			if (i < n - 1)
			{
				close(pfd[i][0]);
				dup2(pfd[i][1], 1);
			}
			char_stop = ft_char_stop(line, process_num + i);
			if (i == n - 1 && (char_stop == '>' || char_stop == 'C'))
			{
				k = ft_chevron_count(line, process_num + i);
				fd[1] = ft_fd(line, process_num + i + k, 0);
				dup2(fd[1], STDOUT);
			}
			else if (i == n - 1 && char_stop == '<')
			{
				k = ft_r_chevron_count(line, process_num + i);
				fd[0] = ft_fd(line, process_num + i + k, 1);
				dup2(fd[0], STDIN);
				k = ft_chevron_count(line, process_num + i + k -1);
				fd[1] = ft_fd(line, process_num + i + k, 0);
				dup2(fd[1], STDOUT);
			}
			if (i > 0)
			{
				close(pfd[i - 1][1]);
				dup2(pfd[i - 1][0], 0);
			}
			ft_word_split(d, line, process_num + i);
			ft_parse_exec(d->word, d);
			ft_free_all_word(d->word);
			if (i == n - 1 && (char_stop == '>' || char_stop == 'C'))
				close(fd[1]);
			if (i == n - 1 && char_stop == '<')
				close(fd[0]);
			exit(g_status);
		}
		else
		{
			waitpid(pid[i], &stats, 0);
			if (i > 0)
				close(pfd[i - 1][0]);
			if (i < n - 1)
				close(pfd[i][1]);
		}
		i++;
	}
}

int		ft_pipe_count(char *line, int process_num)
{
	int		n;
	char	char_stop;
	int		c;

	c = ft_count_process(line);
	n = 1;
	char_stop = '|';
	while (process_num < c && char_stop == '|')
	{
		if ((char_stop = ft_char_stop(line, process_num)) == '|')
			n++;
		process_num++;
	}
	return (n);
}

void	ft_pipe(char *line, t_data *d, int *process_num)
{
	int		n;
	char	char_stop;
	int		i;
	int		fd;

	n = ft_pipe_count(line, *process_num);
	ft_pipe_process(line, d, *process_num, n);
	*process_num = *process_num + n - 1;
	char_stop = ft_char_stop(line, *process_num);
	if (char_stop == '>' || char_stop == 'C')
	{
		n = ft_chevron_count(line, *process_num);
		//printf("chevron count =%d\n", n);
		i = 0;
		while (i < n - 2)
		{
			fd = ft_fd(line, *process_num + i + 2, 0);
			ft_putstr_fd("\0", fd);
			close(fd);
			i++;
		}
		*process_num = *process_num + n - 1;
	}
	else if (char_stop == '<')
	{
		n = ft_r_chevron_count(line, *process_num);
		n = ft_chevron_count(line, *process_num + n - 1);
		i = 0;
		while (i < n - 2)
		{
			fd = ft_fd(line, *process_num + i + 2, 0);
			ft_putstr_fd("\0", fd);
			close(fd);
			i++;
		}
		*process_num = *process_num + n - 1;
	}
}

char	*ft_next_word(char *line, int i)
{
	char	*str;
	int		y;

	y = i;
	while (line[y] && line[y] != ' ' && line[y] != ';' && line[y] != '|'
				&& line[y] != '>' && line[y] != '<')
		y++;
	str = (char *)malloc(sizeof(*str) * (y - i + 1));
	y = 0;
	while (line[i] && line[i] != ' ' && line[i] != ';' && line[i] != '|'
				&& line[i] != '>' && line[i] != '<')
	{
		str[y] = line[i];
		y++;
		i++;
	}
	str[y] = '\0';
	return (str);
}

int		ft_file_fd(char *line, int i, int tmp, int type)
{
	struct stat	stats;
	char		*file;
	int			fd;

	file = ft_next_word(line, i);
	if (type == 0)
	{
		fd = STDOUT;
		if (ft_char_stop(line, tmp - 2) == '>')
			fd = open(file, O_CREAT | O_RDWR | O_TRUNC, 0664);
		else if (ft_char_stop(line, tmp - 2) == 'C')
			fd = open(file, O_CREAT | O_RDWR | O_APPEND, 0664);
	}
	else
	{
		if (stat(file, &stats) == -1)
		{
			g_status = ft_mi_error(file, "No such file or directory", 1);
			fd = -2;
		}
		else
			if (ft_char_stop(line, tmp - 2) == '<')
				fd = open(file, O_RDONLY);
			else
				fd = STDIN;
	}
	free(file);
	return (fd);
}

int		ft_fd(char *line, int process_num, int type)
{
	int		i;
	int		tmp;

	tmp = process_num;
	i = 0;
	while (line[i] && process_num > 1)
	{
		if (line[i] == ';' || line[i] == '|' || line[i] == '>'
				|| line[i] == '<')
		{
			if (line[i + 1] && ((line[i] == '>' && line[i + 1] == '>')
					|| (line[i] == '<' && line[i + 1] == '<')))
				i++;
			process_num--;
		}
		i++;
	}
	while (line[i] && line[i] == ' ')
		i++;
	return (ft_file_fd(line, i, tmp, type));
}

void	ft_chevron_process(char *line, t_data *d, int process_num, int n)
{
	int		pid[n];
	int		stats;
	int		i;
	int		fd;

	ft_free_all_word(d->word);
	d->word = NULL;
	i = 1;
	while (i < n)
	{
		pid[i] = fork();
		if (pid[i] == 0)
		{
			fd = ft_fd(line, process_num + i + 1, 0);
			if (i < n - 1)
				ft_putstr_fd("\0", fd);
			if (i == n - 1)
			{
				dup2(fd, STDOUT);
				ft_word_split(d, line, process_num);
				ft_parse_exec(d->word, d);
				ft_free_all_word(d->word);
			}
			close(fd);
			exit(g_status);
		}
		else
			waitpid(pid[i], &stats, 0);
		i++;
	}
}

int		ft_chevron_count(char *line, int process_num)
{
	int		n;
	char	char_stop;
	int		c;

	c = ft_count_process(line);
	n = 1;
	char_stop = '>';
	while (process_num < c && (char_stop == '>' || char_stop == 'C'))
	{
		char_stop = ft_char_stop(line, process_num);
		if (char_stop == '>' || char_stop == 'C')
			n++;
		process_num++;
	}
	return (n);
}

void	ft_chevron(char *line, t_data *d, int *process_num)
{
	int n;
	int	fd;

	n = ft_chevron_count(line, *process_num);
	ft_chevron_process(line, d, *process_num, n);
	*process_num = *process_num + n - 1;
	if (ft_char_stop(line, *process_num) == '<')
	{
		fd = ft_fd(line, *process_num + 2, 1);
		if (fd != -2)
			close(fd);
	}
	n = ft_r_chevron_count(line, *process_num);
	*process_num = *process_num + n - 1;
}

int		ft_r_b_chevron_process(char *line, t_data *d, int process_num)
{
	int		i;
	int		fd;
	int		n;

	n = ft_chevron_count(line, process_num);
	ft_free_all_word(d->word);
	d->word = NULL;
	i = 1;
	while (i < n)
	{
		fd = ft_fd(line, process_num + i + 1, 0);
		if (i < n - 1)
			ft_putstr_fd("\0", fd);
		if (i == n - 1)
		{
			dup2(fd, STDOUT);
			return (fd);
		}
		close(fd);
		i++;
	}
	return (STDOUT);
}

void	ft_r_chevron_process(char *line, t_data *d, int process_num, int n)
{
	int		pid[n];
	int		stats;
	int		i;
	int		fd;
	int		fd_out;

	ft_free_all_word(d->word);
	d->word = NULL;
	i = 1;
	fd = STDIN;
	fd_out = STDOUT;
	while (i < n)
	{
		fd = ft_fd(line, process_num + i + 1, 1);
		if (fd == -2)
			return ;
		pid[i] = fork();
		if (pid[i] == 0)
		{
			if (i < n - 1)
				ft_putstr_fd("\0", fd);
			if (i == n - 1)
			{
				dup2(fd, STDIN);
				if (ft_char_stop(line, process_num + i) == '>'
						|| ft_char_stop(line, process_num + i == 'C'))
					fd_out = ft_r_b_chevron_process(line, d, process_num + i);
				ft_word_split(d, line, process_num);
				ft_parse_exec(d->word, d);
				ft_free_all_word(d->word);
				close(fd_out);
			}
			close(fd);
			exit(g_status);
		}
		else
		{
			waitpid(pid[i], &stats, 0);
			close(fd);
		
		i++;
	}
}

int		ft_r_chevron_count(char *line, int process_num)
{
	int		n;
	char	char_stop;
	int		c;

	c = ft_count_process(line);
	n = 1;
	char_stop = '<';
	while (process_num < c && char_stop == '<')
	{
		char_stop = ft_char_stop(line, process_num);
		if (char_stop == '<')
			n++;
		process_num++;
	}
	return (n);
}

void	ft_reverse_chevron(char *line, t_data *d, int *process_num)
{
	int n;

	n = ft_r_chevron_count(line, *process_num);
	ft_r_chevron_process(line, d, *process_num, n);
	*process_num = *process_num + n - 1;
	n = ft_chevron_count(line, *process_num);
	*process_num = *process_num + n - 1;
}

int		ft_exec_command(char *line, t_data *d)
{
	int		c;
	int		fd;
	int		process_num;
	int		char_stop;

	if (!line[0])
		return (0);
	c = ft_count_process(line);
	fd = STDOUT;
	process_num = 0;
	if (ft_parse_case(d, line, c) == FALSE)
	{
		g_status = 1;
		return (0);
	}
	while (process_num < c)
	{
		if (ft_word_split(d, line, process_num) == 0)
		{
			ft_print_word(d->word);
			char_stop = ft_char_stop(line, process_num);
			printf("char_stop=%c\n", char_stop);
			if (char_stop == '|')
				ft_pipe(line, d, &process_num);
			else if (char_stop == '>' || char_stop == 'C')
				ft_chevron(line, d, &process_num);
			else if (char_stop == '<')
				ft_reverse_chevron(line, d, &process_num);
			else if (char_stop == 'R')
				ft_mi_error(d->word->data, "<< not supported", 127);
			else
				ft_parse_exec(d->word, d);
		}
		printf("============== NEXT COMMAND ===============\n");
		ft_free_all_word(d->word);
		d->word = NULL;
		process_num++;
	}
	return (0);
}
