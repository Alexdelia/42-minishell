/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolasessayan <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 21:38:27 by nicolases         #+#    #+#             */
/*   Updated: 2021/04/23 21:39:24 by nicolases        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int			ft_chevron_count(char *line, int process_num)
{
	int		n;
	int		ret;
	char	char_stop;

	char_stop = ft_char_stop(line, process_num);
	ret = -1;
	n = -1;
	while (char_stop != ';' && char_stop != '|' && char_stop != '\0')
	{
		char_stop = ft_char_stop(line, process_num);
		n++;
		if (char_stop == '>' || char_stop == 'C')
			ret = n;
		process_num++;
	}
	return (ret);
}

int			ft_reverse_count(char *line, int process_num)
{
	int		n;
	int		ret;
	char	char_stop;

	char_stop = ft_char_stop(line, process_num);
	ret = -1;
	n = -1;
	while (char_stop != ';' && char_stop != '|' && char_stop != '\0')
	{
		char_stop = ft_char_stop(line, process_num);
		n++;
		if (char_stop == '<')
			ret = n;
		process_num++;
	}
	return (ret);
}

int			ft_backward_count(char *line, int process_num)
{
	int		n;
	char	char_stop;

	n = -1;
	while (process_num >= 0)
	{
		char_stop = ft_char_stop(line, process_num);
		if (char_stop == '>' || char_stop == 'C' || char_stop == '<')
			n++;
		else if (char_stop == '\0' || char_stop == ';' || char_stop == '|')
			return (n);
		process_num--;
	}
	return (n);
}

int			forward_to_semi(char *line, int process_num)
{
	int		n;
	char	char_stop;

	char_stop = ft_char_stop(line, process_num);
	n = -1;
	while (char_stop != ';' && char_stop != '|' && char_stop != '\0')
	{
		char_stop = ft_char_stop(line, process_num);
		n++;
		process_num++;
	}
	return (n);
}

void		ft_exec_move(char *line, t_data *d, int process_num, int k)
{
	move_word(line, d, process_num, -k);
	ft_parse_exec(d->word, d);
	move_word(line, d, process_num, k);
}
