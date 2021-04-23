/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_error.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolasessayan <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 21:46:11 by nicolases         #+#    #+#             */
/*   Updated: 2021/04/23 22:48:56 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int			token_error(char *line, t_data *d, int process_num, int char_stop)
{
	if (char_stop == '>' || char_stop == '<')
	{
		move_word(line, d, process_num, 1);
		if (d->word->data[0] == '\0')
		{
			move_word(line, d, process_num, -1);
			return (g_status = ft_mi_error("redirection",
					"syntax error near unexpected token `newline'", 2));
		}
		move_word(line, d, process_num, -1);
	}
	return (0);
}

int			redir_errone(char *line, t_data *d, int process_num, int char_stop)
{
	if (char_stop == 'R')
		return (g_status = ft_mi_error("redirection", "<< not supported", 1));
	if (char_stop == ';' && d->word->data[0] == '\0')
	{
		return (g_status = ft_mi_error("redirection",
			"syntax error near unexpected token `;'", 2));
	}
	if (char_stop == '|' && d->word->data[0] == '\0')
	{
		return (g_status = ft_mi_error("redirection",
			"syntax error near unexpected token `|'", 2));
	}
	if (token_error(line, d, process_num, char_stop) != 0)
		return (1);
	if (process_num > 0 && char_stop == '\0' && d->word->data[0] == '\0'
		&& ft_char_stop(line, process_num - 1) == '|')
	{
		return (g_status = ft_mi_error("redirection",
			"Error: multiligne", 1));
	}
	return (0);
}

int			redir_errall(char *line, t_data *d, int c)
{
	int		status;
	int		process_num;
	char	char_stop;

	process_num = 0;
	while (process_num < c)
	{
		char_stop = ft_char_stop(line, process_num);
		status = ft_word_split(d, line, process_num);
		if (status == 0)
		{
			if (redir_errone(line, d, process_num, char_stop) != 0)
			{
				ft_free_all_word(d->word);
				d->word = NULL;
				return (1);
			}
		}
		ft_free_all_word(d->word);
		d->word = NULL;
		process_num++;
		if (status == -1)
			return (1);
	}
	return (0);
}
