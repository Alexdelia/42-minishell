/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_call_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolasessayan <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 12:57:41 by nicolases         #+#    #+#             */
/*   Updated: 2021/04/25 13:00:04 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void		move_word(char *line, t_data *d, int process_num, int n)
{
	ft_free_all_word(d->word);
	ft_word_split(d, line, process_num + n);
}

int			**init_pfd(int c)
{
	int i;
	int **pfd;

	pfd = malloc(sizeof(*pfd) * c);
	i = 0;
	while (i < c)
	{
		pfd[i] = malloc(sizeof(**pfd) * 2);
		i++;
	}
	return (pfd);
}

void		free_pfd(int **pfd, int c)
{
	int i;

	i = 0;
	while (i < c)
	{
		free(pfd[i]);
		i++;
	}
	free(pfd);
}

static int	ft_is_double_c(char *line, int i, char c)
{
	if (line[i] && line[i + 1] && line[i] == c && line[i + 1] == c)
		return (TRUE);
	return (FALSE);
}

char		ft_char_stop(char *line, int process_num)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\"')
		{
			i++;
			while (line[i] && (line[i] != '\"' || (line[i - 1]
					&& line[i - 1] == '\\' && line[i] == '\"')))
				i++;
		}
		else if (line[i] == '\'')
		{
			i++;
			while (line[i] && (line[i] != '\'' || (line[i - 1]
					&& line[i - 1] == '\\' && line[i] == '\'')))
				i++;
		}
		else if (line[i] && (line[i] == ';' || line[i] == '|'
			|| line[i] == '>' || line[i] == '<')
			&& (!line[i - 1] || (line[i - 1] && line[i - 1] != '\\')))
		{
			if (process_num == 0)
			{
				if (ft_is_double_c(line, i, '>') == TRUE)
					return ('C');
				if (ft_is_double_c(line, i, '<') == TRUE)
					return ('R');
				return (line[i]);
			}
			if (ft_is_double_c(line, i, '>') == TRUE
					|| ft_is_double_c(line, i, '<') == TRUE)
				i++;
			process_num--;
		}
		i++;
	}
	return ('\0');
}
