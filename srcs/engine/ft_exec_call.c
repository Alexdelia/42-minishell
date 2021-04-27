/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_call.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolasessayan <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 18:17:39 by nicolases         #+#    #+#             */
/*   Updated: 2021/04/26 10:43:11 by adelille         ###   ########.fr       */
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

void		ft_exec_word(char *line, t_data *d, int *process_num, int **pfd)
{
	char		char_stop;

	char_stop = ft_char_stop(line, *process_num);
	if (char_stop == ';' || char_stop == '\0')
		ft_semi(line, d, *process_num, pfd);
	else if (char_stop == '|')
		ft_pipe(line, d, *process_num, pfd);
	else if (char_stop == '>' || char_stop == 'C' || char_stop == '<')
		ft_chevron(line, d, process_num, pfd);
}

void		ft_exec_command(char *line, t_data *d)
{
	int		c;
	int		process_num;
	int		**pfd;

	if (!line[0])
		return ;
	c = ft_count_process(line);
	if (redir_errall(line) == 1)
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
