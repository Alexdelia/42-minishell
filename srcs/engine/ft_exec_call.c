/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_call.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 09:49:19 by adelille          #+#    #+#             */
/*   Updated: 2021/04/14 20:52:27 by adelille         ###   ########.fr       */
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

int		ft_exec_command(char *line, t_data *d)
{
	int		c;
	int		fd;
	int		process_num;

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
			fd = ft_redirection(line, process_num);
			ft_parse_exec(d->word, d, fd);
			printf("========= NEXT COMMAND =============\n");
		}
		ft_free_all_word(d->word);
		d->word = NULL;
		process_num++;
	}
	return (0);
}
