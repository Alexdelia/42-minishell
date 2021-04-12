/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_call.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 09:49:19 by adelille          #+#    #+#             */
/*   Updated: 2021/04/12 13:37:01 by nicolases        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		ft_parse_exec(t_word *word, t_data *d, int fd)
{
	if (ft_strcmp(word->data, "echo") == 0)
		status = ft_echo(fd, word->next);
	else if (ft_strcmp(word->data, "cd") == 0)
		status = ft_cd(word->next->data);
	else if (ft_strcmp(word->data, "pwd") == 0)
		status = ft_pwd(fd);
	else if (ft_strcmp(word->data, "export") == 0)
		status = ft_export(word->next, &(d->env), fd);
	else if (ft_strcmp(word->data, "unset") == 0)
		status = ft_unset(word->next, &(d->env));
	else if (ft_strcmp(word->data, "env") == 0)
		status = ft_env(fd, d->env);
	else if (word->data[0] && (word->data[0] == '.'
			|| word->data[0] == '/'))
		status = ft_exec(word->data, word->next->data, d->env, fd);
	else if (ft_statable(&word, d->env) == TRUE)
		status = ft_exec(word->data, word->next->data, d->env, fd);
	else if (is_included(word->data, '='))
		status = ft_mi_error(word->data, "in-line arg not supported", 127);
	else
		status = ft_mi_error(word->data, "command not found", 127);
	ft_free_all_word(word);
	//kill(pid, SIGKILL);
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
	//int		pid;
	int		fd;
	int		process_num;

	if (!line[0])
		return (0);
	c = ft_count_process(line);
	fd = STDOUT;
	process_num = 0;
	while (process_num < c)
	{
		//pid = fork();
		ft_word_split(d, line, process_num);
		//if (!(word = ft_word_split(d, line, process_num)))
		//	return (0);
		//ft_ps(word->data);
		//ft_print_word(word);
		//if (base_p_num > 1)
		//	fd = ft_redirection(line, base_p_num - process_num);
		ft_print_word(d->word);
		printf("========= NEXT COMMAND =============\n");
		ft_free_all_word(d->word);
		// fd = ft_parse_exec(word, d, fd);
		process_num++;
	}
	return (0);
}
