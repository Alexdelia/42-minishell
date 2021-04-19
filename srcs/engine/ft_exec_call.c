/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_call.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 09:49:19 by adelille          #+#    #+#             */
/*   Updated: 2021/04/19 22:47:13 by adelille         ###   ########.fr       */
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

void	ft_pipe_process(char *line, t_data *d, int process_num, int n)
{
	int	pid[n];
	int	pfd[n-1][2];
	int	stats;
	int i;

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
			if (i > 0)
			{
				close(pfd[i - 1][1]);
				dup2(pfd[i - 1][0], 0);
			}
			ft_word_split(d, line, process_num + i);
			ft_parse_exec(d->word, d, STDOUT);
			ft_free_all_word(d->word);
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

int		ft_pipe_count(char *line, int c, int process_num)
{
	int		n;
	char	char_stop;

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

void	ft_pipe(char *line, t_data *d, int c, int *process_num)
{
	int n;

	n = ft_pipe_count(line, c, *process_num);
	printf("pipe count = %d\n", n);
	ft_pipe_process(line, d, *process_num, n);	
	*process_num = *process_num + n - 1;
	//add >> and >
}

char	*ft_chevron_file(char *line, int process_num)
{
	int		i;

	i = 0;
	while (line[i] && process_num > 1)
	{
		if (line[i] == ';' || line[i] == '|' || line[i] == '>' || line[i] == '<')
		{
			if (line[i + 1] && ((line[i] == '>' && line[i + 1] == '>')
					|| (line[i] == '<' && line[i + 1] == '<')))
				i++;
			process_num--;
		}
		i++;
	}
	if (line[i] == ' ')
		i++;
	return (ft_next_word(line, i));
}

void	ft_chevron_process(char *line, t_data *d, int process_num, int n)
{
	int		pid[n];
	int		pfd[2];
	int		stats;
	int		i;
	int		fd;
	char	*file;

	ft_free_all_word(d->word);
	d->word = NULL;
	i = 1; // Start at one, can be change if you want to stick to pipe. but change all line with: //CH . if you break it I will be able to redo it, np :3
	while (i < n) //CH
	{
		pipe(pfd);
		pid[i] = fork();
		if (pid[i] == 0)
		{
			fd = STDOUT; // IMPORTANT
			file = ft_chevron_file(line, process_num + i + 1); //CH 
			if (ft_char_stop(line, process_num + i - 1) == '>') //CH
				fd = open(file, O_CREAT | O_RDWR | O_TRUNC, 0664);
			else if (ft_char_stop(line, process_num + i - 1) == 'C') //CH
				fd = open(file, O_CREAT | O_RDWR | O_APPEND, 0664);
			free(file);
			/*	if (i < n - 1)
				{
				close(pfd[i][0]);
				dup2(pfd[i][1], 1);
				}
				if (i > 0)
				{
				close(pfd[i - 1][1]);
				dup2(pfd[i - 1][0], fd);
				}*/
			if (i < n - 1) //CH
				ft_putstr_fd("\0", fd); // IMPORTANT
			if (i == n - 1) //CH
			{
				dup2(fd, STDOUT);
				//dup2(pfd[1], STDOUT);
				//dup2(pfd[0], fd);
				ft_word_split(d, line, process_num);
				ft_parse_exec(d->word, d, STDOUT);
				ft_free_all_word(d->word);
				close(pfd[0]);
				close(pfd[1]);
			}
			close(fd);
			exit(g_status);
		}
		else
		{
			waitpid(pid[i], &stats, 0);
			close(pfd[0]);
			close(pfd[1]);
		}
		i++;
	}
}

int	ft_chevron_count(char *line, int c, int process_num)
{
	int		n;
	char	char_stop;

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

void	ft_chevron(char *line, t_data *d, int c, int *process_num)
{
	int n;
	(void)line;
	(void)d;
	n = ft_chevron_count(line, c, *process_num);
	ft_chevron_process(line, d, *process_num, n);
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
	while (process_num < c)
	{
		if (ft_word_split(d, line, process_num) == 0)
		{
			ft_print_word(d->word);//
			char_stop = ft_char_stop(line, process_num);
			printf("char_stop=%c\n", char_stop);//
			if (char_stop == '|')
				ft_pipe(line, d, c, &process_num);
			else if (char_stop == '>' || char_stop == 'C')
				ft_chevron(line, d, c, &process_num);
			else if (char_stop == '<')
				ft_mi_error(d->word->data, "< is work-in-progress", 127);
			else if (char_stop == 'R')
				ft_mi_error(d->word->data, "<< not supported", 127);
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
