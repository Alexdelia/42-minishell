/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_case.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 11:12:00 by adelille          #+#    #+#             */
/*   Updated: 2021/04/21 16:31:02 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_chevron_case(char *line, int i, char char_stop)
{
	if (char_stop == '>')
		return (ft_mi_error("syntax error near  unexpected token",
					"'>'", FALSE));
	else if (char_stop == 'C')
		return (ft_mi_error("syntax error near  unexpected token",
					"'>>'", FALSE));
	else if (char_stop == '<')
		return (ft_mi_error("syntax error near  unexpected token",
					"'<'", FALSE));
	return (TRUE);
}

static int	ft_case(t_data *d, char *line, int i)
{
	char	char_stop;

	if (!d->word->data[0])
	{
		char_stop = ft_char_stop(line, process_num);
		if (char_stop == ';')
			return (ft_mi_error("syntax error near unexpected token",
						"';'", FALSE));
		else if (char_stop == '|')
			return (ft_mi_error("syntax error near  unexpected token",
						"'|'", FALSE));
		while (line[i] && (line[i] == ' '
					|| line[i] == '>' || line[i] == '<'))
			i++;
		if (!line[i])
		{
			if (ft_chevron_case(line, i, char_stop) == FALSE)
				return (FALSE);
		}
	}
	return (TRUE);
}

int			ft_parse_case(t_data *d, char *line, int c)
{
	int		status;
	int		i;
	int		process_num;

	i = 0;
	process_num = 0;
	char_stop = 0;
	while (process_num < c)
	{
		status = ft_word_split(d, line, process_num);
		if (status == 0)
		{
			if (ft_case(d, line, i) == FALSE)
				return (FALSE);
		}
		ft_free_all_word(d->word);
		d->word = NULL;
		process_num++;
		if (status == -1)
			return (FALSE);
	}
	return (TRUE);
}
