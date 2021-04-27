/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolasessayan <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 15:53:13 by nicolases         #+#    #+#             */
/*   Updated: 2021/04/26 17:43:43 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char		*ft_next_word(char *line, int i)
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

int			ft_fd_index(char *line, int process_num)
{
	int		i;

	process_num;
	i = 0;
	while (line[i] && process_num > 0)
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
	return (i);
}

int			ft_fd_out(char *line, int process_num, char char_stop)
{
	int		fd;
	char	*file;
	int		i;

	i = ft_fd_index(line, process_num + 1);
	file = ft_next_word(line, i);
	fd = STDOUT;
	if (char_stop == '>')
		fd = open(file, O_CREAT | O_RDWR | O_TRUNC, 0664);
	else if (char_stop == 'C')
		fd = open(file, O_CREAT | O_RDWR | O_APPEND, 0664);
	free(file);
	return (fd);
}

int			ft_fd_in(char *line, int process_num)
{
	int			fd;
	char		*file;
	int			i;
	struct stat	stats;

	i = ft_fd_index(line, process_num + 1);
	file = ft_next_word(line, i);
	if (stat(file, &stats) == -1)
	{
		fd = -1;
		g_status = ft_mi_error(file, "No such file or directory", 1);
	}
	else
		fd = open(file, O_RDONLY);
	free(file);
	return (fd);
}

int			check_build_fd(char *line, int process_num, int **pfd)
{
	char char_stop;

	char_stop = ft_char_stop(line, process_num);
	while (char_stop != ';' && char_stop != '!' && char_stop != '\0')
	{
		char_stop = ft_char_stop(line, process_num);
		if (char_stop == '>' || char_stop == 'C')
		{
			pfd[process_num][1] = ft_fd_out(line, process_num,
				ft_char_stop(line, process_num));
			close(pfd[process_num][1]);
		}
		else if (char_stop == '<')
		{
			pfd[process_num][0] = ft_fd_in(line, process_num);
			if (pfd[process_num][0] == -1)
				return (1);
			close(pfd[process_num][0]);
		}
		process_num++;
	}
	return (0);
}
