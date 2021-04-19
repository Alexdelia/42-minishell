/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 11:46:13 by adelille          #+#    #+#             */
/*   Updated: 2021/04/16 10:08:57 by nicolases        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_next_word(char *line, int i)
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

/*int		ft_pipe(char *line, int i)
{
	char	*bin;

	bin = ft_next_word(line, i + 1);
	//if (pipe(pfd) == -1);
	//	ft_mi_error("pipe", "It might explode you know.\n", 0);
	//
	free(bin);
	return (0);
}*/

int		ft_chevron(char *line, int i)
{
	int		fd;
	char	*file;

	if (line[i] && line[i] == '>')
	{
		file = ft_next_word(line, i + 2);
		fd = open(file, O_CREAT | O_APPEND | O_RDWR, 0664);
	}
	else
	{
		file = ft_next_word(line, i + 1);
		fd = open(file, O_CREAT | O_RDWR | O_TRUNC, 0664);
	}
	//ft_ps(file);
	//ft_ps("\n");
	free(file);
	return (fd);
}

int		ft_redirection(char *line, int process_num, int *char_stop)
{
	int	fd;
	int	i;

	i = 0;
	fd = STDOUT;
	(*char_stop) = 0;
	while (line[i] && process_num >= 0)
	{
		if (line[i] == '|' && process_num == 0)
		{
			// fd = ft_pipe(line, i + 1);
			(*char_stop) = PIPE;
		}
		else if (line[i] == '>' && process_num == 0)
		{
			fd = ft_chevron(line, i + 1);
			(*char_stop) = CHEVRON;
		}
		if (line[i] == '|' || line[i] == '>')
		{
			if (line[i + 1] && line[i + 1] == '>')
				i++;
			process_num--;
		}
		i++;
	}
	return (fd);
}
