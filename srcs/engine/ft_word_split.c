/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_word_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 06:51:14 by adelille          #+#    #+#             */
/*   Updated: 2021/04/27 14:22:00 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		get_start_index(char *line, int process_num, int quote)
{
	int	i;

	i = 0;
	while (line[i] != '\0' && process_num > 0)
	{
		quote = ft_char_quote(line, i);
		if (quote != -1)
			i = quote;
		else if (line[i] == '|' || line[i] == ';')
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

int		get_end_index(char *line, int start)
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

int		ft_error_ml(void)
{
	ft_pserc("Error: multiligne\n", RED);
	return (-1);
}

int		ft_word_split(t_data *d, char *line, int process_num)
{
	int		i;
	int		j;
	char	*raw;
	char	*clean;
	char	*end_of_line;

	i = get_start_index(line, process_num, 0);
	j = get_end_index(line, i);
	raw = ft_strdup2(line, i, j);
	clean = ft_strtrim(raw, " ");
	free(raw);
	ft_transform(d, clean, TRUE);
	free(clean);
	end_of_line = ft_strdup(&line[j]);
	ft_transform(d, end_of_line, FALSE);
	free(end_of_line);
	return (0);
}
