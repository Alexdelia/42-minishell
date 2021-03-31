/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_call.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 09:49:19 by adelille          #+#    #+#             */
/*   Updated: 2021/03/31 11:45:57 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	exec will be call with the big STR read by gnl and t_env *env
**
**	it will be in a child process that will need to be kill and parent will be able to restart
**
**	this child process (I will call it: calling process), will call process for each command
*/

int	ft_parse_exec(t_word *word, t_env *env, int actual_p, int total_p, int fd)
{
	/*if (actual_p < total_p)
		fd += 2;*/
	if (ft_strcmp(word->data, "echo") == 0)
		ft_echo(fd, word->next, env);
	else if (ft_strcmp(word->data, "cd") == 0)
		ft_cd(word->data);
	else if (ft_strcmp(word->data, "pwd") == 0)
		ft_pwd(fd);
	/*
	else if (ft_strcmp(word->data, "export") == 0)
		ft_export();
	else if (ft_strcmp(word->data, "unset") == 0)
		ft_unset(word, env);
	*/
	else if (ft_strcmp(word->data, "env") == 0)
		ft_env(fd, *env);
	ft_free_all_word(word);
	kill();
}

int	ft_count_process(char *line)
{
	int	process_num;

	process_num = 1;
	while (line[i])
	{
		if (line[i] == '|' || line[i] == ';')
			process_num++;
		else if (line[i] == '>' || line[i] == '<')
		{
			process_num++;
			if (line[i + 1] && (line [i + 1] == '>' || line[i + 1] == '<'))
				i++;
		}
		i++;
	}
}

int	ft_exec_command(char *line, t_env *env)
{
	int		process_num;
	int		base_p_num;
	int		pid;
	int		fd;
	t_word	*word;

	process_num = ft_count_process(line);
	base_p_num = process_num;
	fd = STDOUT;
	while(process > 0)
	{
		pid = fork();
		if (pid == 0)
		{
			word = ft_word(line, base_p_num - process_num);
			if (base_p_num > 1)
				fd = ft_redirection(line, base_p_num - process_num);
			fd = ft_parse_exec(word, env, base_p_num - process_num, base_p_num, fd);
		}
		else if (pid != 0)
		{
			wait(NULL);
			process_num--;
		}
	}
	return (0);
}
