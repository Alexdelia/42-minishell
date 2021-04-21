/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_case.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 11:12:00 by adelille          #+#    #+#             */
/*   Updated: 2021/04/21 15:11:09 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_parse_case(t_data *d, char *line, int c)
{
	int		process_num;
	char	char_stop;

	process_num = 0;
	char_stop = 0;
	while (process_num < c)
	{
		if(ft_word_split(d, line, process_num) == 0)
		{
			if (!d->word->data[0])
			{
				char_stop = ft_char_stop(line, process_num);
				if (char_stop == ';')
					return (ft_mi_error("syntax error near unexpected token",
						"';'", FALSE));
				else if (char_stop == '|')
					return (ft_mi_error("syntax error near  unexpected token",
						"'|'", FALSE));
				else if (char_stop == '>')
					return (ft_mi_error("syntax error near  unexpected token",
						"'>'", FALSE));
				else if (char_stop == 'C')
					return (ft_mi_error("syntax error near  unexpected token",
						"'>>'", FALSE));
				else if (char_stop == '<')
					return (ft_mi_error("syntax error near  unexpected token",
						"'<'", FALSE));
			}	
		}
		ft_free_all_word(d->word);
		d->word = NULL;
		process_num++;
	}
	return (TRUE);
}
