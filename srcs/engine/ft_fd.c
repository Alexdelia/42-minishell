/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolasessayan <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 15:53:13 by nicolases         #+#    #+#             */
/*   Updated: 2021/04/22 18:14:47 by nicolases        ###   ########.fr       */
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
	int		tmp;

	tmp = process_num;
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
	//printf("*** char_stop = %c ***\n", char_stop);
	//printf("*** STDOUT file = %s ***\n", file);
	fd = STDOUT;
	if (char_stop == '>')
		fd = open(file, O_CREAT | O_RDWR | O_TRUNC, 0664);
	else if (char_stop == 'C')
		fd = open(file, O_CREAT | O_RDWR | O_APPEND, 0664);
	free(file);
	return (fd);
}

int			ft_fd_in(char *line, int process_num, char char_stop)
{
	int		fd;
	char	*file;
	int		i;

	(void)char_stop;
	i = ft_fd_index(line, process_num + 1);
	file = ft_next_word(line, i);
	//printf("*** char_stop = %c ***\n", char_stop);
	//printf("*** STDIN file = %s ***\n", file);
	fd = open(file, O_RDONLY);
	free(file);
	return (fd);
}
