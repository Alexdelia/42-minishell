/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_word_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 06:51:14 by adelille          #+#    #+#             */
/*   Updated: 2021/04/12 16:26:20 by nicolases        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	get_start_index(char *line, int process_num)
{
	int	i;

	i = 0;
	while (line[i] != '\0' && process_num > 0)
	{
		if (line[i] == '|' || line[i] == ';')
			process_num--;
		else if (line[i] == '>')
		{
			process_num--;
			if (line[i + 1] != '\0' && line[i + 1] == '>')
				i++;
		}
		else if (line[i] == '<')
		{
			process_num--;
			if (line[i + 1] != '\0' && line[i + 1] == '<')
				i++;
		}
		i++;
	}
	return (i);
}

int	get_end_index(char *line, int start)
{
	int	j;

	j = start;
	while (line[j] != '\0' && line[j] == ' ')
		j++;
	while (line[j] != '\0' && line[j] != ';' && line[j] != '|'
		&& line[j] != '<' && line[j] != '>' && line[j] != ' ')
		j++;
	while (line[j] != '\0' && line[j] == ' ')
		j++;
	return (j);
}

static void	ft_error_ml(void)
{
	ft_pserc("Error: multiligne\n", RED);
	return ;
}

void	ft_word_split(t_data *d, char *line, int process_num)
{
	int		i;
	int		j;
	char	*raw;
	char	*clean;
	char	*end_of_line;

	i = get_start_index(line, process_num);
	j = get_end_index(line, i);
	raw = ft_strdup2(line, i, j);
	clean = ft_strtrim(raw, " ");
	free(raw);
	if (ft_transform(d, clean, TRUE) < 0)
	{
		free(clean);
		return (ft_error_ml());
	}
	free(clean);
	end_of_line = ft_strdup(&line[j]);
	if (ft_transform(d, end_of_line, FALSE) < 0)
	{
		free(end_of_line);
		return (ft_error_ml());
	}
	free(end_of_line);
}
