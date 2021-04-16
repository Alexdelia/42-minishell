/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_call.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 09:49:19 by adelille          #+#    #+#             */
/*   Updated: 2021/04/16 17:48:43 by nicolases        ###   ########.fr       */
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

void		ft_pipe(char *line, t_data *d, int *process_num, int fd)
{
	t_word	*next;
	int 	pfd[2];
	int 	pid;
	int	exec_status;

	(void)fd;
	exec_status = 0;
	next = ft_new_word(d->word->data);
	ft_add_back_word(&next, ft_new_word(d->word->next->data));
	ft_free_all_word(d->word);
	d->word = NULL;
	*process_num = *process_num + 1;
	ft_word_split(d, line, *process_num);
	//printf("ENTERING PIPE\n");
	pid = fork();
	pipe(pfd);
	if (pid == 0)
	{
		//printf("CHILD ARG = \n");
		//ft_print_word(d->word);
		close(pfd[1]);
		dup2(pfd[0], 0);
		close(pfd[0]);
		ft_parse_exec(d->word, d, fd);
	}
	else
	{
		//close(pfd[0]);
		//dup2(pfd[1], 1);
		//close(pfd[1]);
		printf("PARENT ARG = \n");
		ft_print_word(next);
		//ft_parse_exec(next, d, fd);
	}
	ft_free_all_word(next);
	next = NULL;
	//printf("EXITING PIPE\n");
}

/*void		ft_pipe(char *line, t_data *d, int *process_num, int fd)
{
	int     pid;
	int     pfd[2];
	//int	exec_status;

	(void)line;
	(void)d;
	(void)process_num;
	(void)fd;
	pipe(pfd);
	pid = fork();
	
	if (pid == 0)
	{
		close(pfd[0]);
		dup2(pfd[1], 1);
		close(pfd[1]);
		//printf("Child is here\n");
		//sleep(3);
		exit(1);
	}
	else
	{
		close(pfd[1]);
		dup2(pfd[0], 0);
		close(pfd[0]);
		//waitpid(pid, &exec_status, 0);
		//printf("Parent is ready\n");
	}
	dup2(1, 1);
	dup2(0, 0);
}*/

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
	char_stop = 0;
	while (process_num < c)
	{
		if (ft_word_split(d, line, process_num) == 0)
		{
			ft_print_word(d->word);//
			fd = ft_redirection(line, process_num, &char_stop);
			if (char_stop == CHEVRON)
				printf("CHEVRON\n");
			else if (char_stop == PIPE)
				ft_pipe(line, d, &process_num, fd);
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
