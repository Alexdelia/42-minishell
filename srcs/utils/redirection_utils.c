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
