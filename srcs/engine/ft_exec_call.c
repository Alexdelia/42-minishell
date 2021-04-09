/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_call.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 09:49:19 by adelille          #+#    #+#             */
/*   Updated: 2021/04/09 15:27:13 by nicolases        ###   ########.fr       */
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
	/*else if ( xxx )
		ft_exec(word->data, *word->next, *env, fd);*/
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
	while (line[i])
	{
		if (line[i] == '|' || line[i] == ';')
			process_num++;
		else if (line[i] == '>' || line[i] == '<')
		{
			process_num++;
			if (line[i + 1] && (line[i + 1] == '>' || line[i + 1] == '<'))
				i++;
		}
		i++;
	}
	return (process_num);
}

void	ft_print_word(t_word *word)
{
	while (word)
	{
		ft_ps(word->data);
		ft_ps("\n");
		word = word->next;
	}
}

int		ft_exec_command(char *line, t_data *d)
{
	int		process_num;
	int		base_p_num;
	//int		pid;
	int		fd;
	t_word	*word;

	if (!line[0])
		return (0);
	process_num = ft_count_process(line);
	base_p_num = process_num;
	fd = STDOUT;
	while (process_num > 0)
	{
		//pid = fork();
		if (!(word = ft_word_split(d, line, base_p_num - process_num)))
			return (0);
		//ft_ps(word->data);
		//ft_print_word(word);
		//if (base_p_num > 1)
		//	fd = ft_redirection(line, base_p_num - process_num);
		fd = ft_parse_exec(word, d, fd);
		process_num--;
	}
	return (0);
}
