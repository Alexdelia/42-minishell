/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_call.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 09:49:19 by adelille          #+#    #+#             */
/*   Updated: 2021/04/19 09:56:23 by nicolases        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		ft_parse_exec(t_word *word, t_data *d, int fd)
{
	if (ft_strcmp(word->data, "echo") == 0)
		g_status = ft_echo(fd, word->next);
	else if (ft_strcmp(word->data, "cd") == 0)
		g_status = ft_cd(word->next->data);
	else if (ft_strcmp(word->data, "pwd") == 0)
		g_status = ft_pwd(fd);
	else if (ft_strcmp(word->data, "export") == 0)
		g_status = ft_export(word->next, &(d->env), fd);
	else if (ft_strcmp(word->data, "unset") == 0)
		g_status = ft_unset(word->next, &(d->env));
	else if (ft_strcmp(word->data, "env") == 0)
		g_status = ft_env(fd, d->env);
	else if (ft_strcmp(word->data, "exit") == 0)
		g_status = ft_exit(d);
	else if (word->data[0] && (word->data[0] == '.'
			|| word->data[0] == '/'))
		g_status = ft_exec(word, d->env, fd);
	else if (ft_statable(&word, d->env) == TRUE)
		g_status = ft_exec(word, d->env, fd);
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

void	ft_print_word(t_word *word)
{
	while (word != NULL)
	{
		ft_ps(word->data);
		ft_ps("|");
		ft_ps("\n");
		word = word->next;
	}
}

void		ft_pipe(char *line, t_data *d, int *process_num, int n)
{
	int	pid[n];
	int	pfd[n-1][2];
	int	stats;
	int i;

	ft_free_all_word(d->word);
	d->word = NULL;

	i = 0;
	pipe(pfd[i]);
	pid[i] = fork();
	if (pid[i] == 0)
	{
		close(pfd[i][0]);
		dup2(pfd[i][1], 1);
		/* NO ENTRY TO CLOSE*/
		ft_word_split(d, line, *process_num + i);
		ft_parse_exec(d->word, d, STDOUT);
		ft_free_all_word(d->word);
		exit(g_status);
	}
	else
	{
		waitpid(pid[i], &stats, 0);
		/* NO EXIT TO WAIT FOR*/
		close(pfd[i][1]);
	}

	i = 1;
	pipe(pfd[i]);
	pid[i] = fork();
	if (pid[i] == 0)
	{
		close(pfd[i][0]);
		dup2(pfd[i][1], 1);
		close(pfd[i - 1][1]);
		dup2(pfd[i - 1][0], 0);
		ft_word_split(d, line, *process_num + i);
		ft_parse_exec(d->word, d, STDOUT);
		ft_free_all_word(d->word);
		exit(g_status);
	}
	else
	{
		waitpid(pid[i], &stats, 0);
		close(pfd[i - 1][0]);
		close(pfd[i][1]);
	}

	i = 2;
	pipe(pfd[i]);
	pid[i] = fork();
	if (pid[i] == 0)
	{
		close(pfd[i][0]);
		dup2(pfd[i][1], 1);
		close(pfd[i - 1][1]);
		dup2(pfd[i - 1][0], 0);
		ft_word_split(d, line, *process_num + i);
		ft_parse_exec(d->word, d, STDOUT);
		ft_free_all_word(d->word);
		exit(g_status);
	}
	else
	{
		waitpid(pid[i], &stats, 0);
		close(pfd[i - 1][0]);
		close(pfd[i][1]);
	}

	i = 3;
	pid[i] = fork();
	/* NO PIPE TO INIT */
	if (pid[i] == 0)
	{
		/* NO EXIT TO CLOSE*/
		close(pfd[i - 1][1]);
		dup2(pfd[i - 1][0], 0);
		ft_word_split(d, line, *process_num + i);
		ft_parse_exec(d->word, d, STDOUT);
		ft_free_all_word(d->word);
		exit(g_status);
	}
	else
	{
		waitpid(pid[i], &stats, 0);
		close(pfd[i - 1][0]);
		/*NO ENTRTY TO WAIT FOR*/
	}
	*process_num = *process_num + i;
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
	while (process_num < c)
	{
		if (ft_word_split(d, line, process_num) == 0)
		{
			ft_print_word(d->word);
			char_stop = ft_char_stop(line, process_num);
			printf("char_stop=%c|\n", char_stop);
			if (char_stop == '|')
			else if (char_stop == '>' || char_stop == 'C')
				ft_mi_error("", "> and >> are work-in-progress", 127);
			else if (char_stop == '<')
				ft_mi_error("", "< is work-in-progress", 127);
			else if (char_stop == 'R')
				ft_mi_error("", "<< is not supported", 127);
			else
				ft_parse_exec(d->word, d, fd);
			printf("========= NEXT COMMAND =============\n");//
		}
		ft_free_all_word(d->word);
		d->word = NULL;
		process_num++;
	}
	return (0);
}
