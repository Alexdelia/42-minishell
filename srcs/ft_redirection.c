/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 11:46:13 by adelille          #+#    #+#             */
/*   Updated: 2021/03/31 12:20:46 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_next_word(char *line, int i)
{
	char	str[PATH_LEN];
	int		y;

	y = i;
	while (line[y] != ' ')
		y++;
	y = 0;
	while (line[i] != ' ')
	{
		str[y] = line[i];
		y++;
		i++;
	}
	str[y + 1] = '\0';
	return (str);
}

int		ft_pipe(char *line, int i)
{
	int		fd;
	char	*bin;

	bin = ft_next_word(line, i + 1);
	fd = STDOUT;
	//
	return (fd);
}

int		ft_chevron(char *line, int i)
{
	int		fd;
	char	*file;

	file = ft_next_word(line, i + 1);
	if (line[i] && line[i] == '>')
		fd = open(file, O_CREAT | O_APPEND | O_WRONLY);
	else
		fd = open(file, O_CREAT | O_WRONLY);
	return (fd);
}

int		ft_redirection(char *line, int process_num)
{
	int	fd;
	int	i;

	i = 0;
	fd = STDOUT;
	while (line[i] && process_num >= 0)
	{
		if (line[i] == '|' && process_num == 0)
			fd = ft_pipe(line, i + 1);
		else if (line[i] == '>' && process_num == 0)
			fd = ft_chevron(line, i + 1);
		if (line[i] == '|' || line[i] == '>')
		{
			if (line[i + 1] && line[i + 1] == '>')
				++;
			process_num--;
		}
	}
	return (fd);
}