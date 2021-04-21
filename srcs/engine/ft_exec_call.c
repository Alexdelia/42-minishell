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

int			ft_count_process(char *line)
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

void		ft_pipe(char *line, t_data *d, int process_num, int **pfd)
{
	int		pid;
	int		stats;

	(void)line;
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
		ft_parse_exec(d->word, d);
		exit(g_status);
	}
	else
	{
		waitpid(pid, &stats, 0);
		if (process_num > 0 && ft_char_stop(line, process_num - 1) == '|')
			close(pfd[process_num - 1][0]);
		close(pfd[process_num][1]);
		printf("=== WORD EXECUTED IN CHILD ===\n");
	}
}

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
		ft_parse_exec(d->word, d);
		exit(g_status);
	}
	else
	{
		waitpid(pid, &stats, 0);
		if (process_num > 0 && ft_char_stop(line, process_num - 1) == '|')
			close(pfd[process_num - 1][0]);
		printf("=== WORD EXECUTED IN CHILD ===\n");
	}
}

void		ft_exec_word(char *line, t_data *d, int process_num, int **pfd)
{
	char	char_stop;

	(void)pfd;
	char_stop = ft_char_stop(line, process_num);
	ft_print_word(d->word);
	printf("char_stop=%c\n", char_stop);
	if (char_stop == '|')
		ft_pipe(line, d, process_num, pfd);
	else if (char_stop == '>' || char_stop == 'C')
	{
		ft_parse_exec(d->word, d);
		printf("=== WORD EXECUTED IN PARENT ===\n");
	}
	else if (char_stop == ';' || char_stop == '\0')
		ft_semi(line, d, process_num, pfd);
	else if (char_stop == '<' || char_stop == 'R')
	{
		ft_mi_error(d->word->data, "< and << not supported", 127);
		printf("=== WORD NOT EXECUTED ===\n");
	}
	else
	{
		ft_mi_error(d->word->data, "separator not recognized", 127);
		printf("=== WORD NOT EXECUTED ===\n");
	}
}

int			**init_pfd(int c)
{
	int i;
	int **pfd;

	pfd = malloc(sizeof(*pfd) * c);
	i = 0;
	while (i < c)
	{
		pfd[i] = malloc(sizeof(**pfd) * 2);
		i++;
	}
	return (pfd);
}

void		free_pfd(int **pfd, int c)
{
	int i;

	i = 0;
	while (i < c)
	{
		free(pfd[i]);
		i++;
	}
	free(pfd);
}

void		ft_exec_command(char *line, t_data *d)
{
	int		c;
	int		process_num;
	int		**pfd;

	if (!line[0])
		return ;
	c = ft_count_process(line);
	pfd = init_pfd(c);
	process_num = 0;
	while (process_num < c)
	{
		if (ft_word_split(d, line, process_num) == 0)
			ft_exec_word(line, d, process_num, pfd);
		ft_free_all_word(d->word);
		d->word = NULL;
		process_num++;
	}
	free_pfd(pfd, c);
}
