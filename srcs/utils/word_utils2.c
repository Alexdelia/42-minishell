/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolasessayan <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 19:01:36 by nicolases         #+#    #+#             */
/*   Updated: 2021/04/13 17:51:40 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		ft_word_search(char *str, t_word *word)
{
	while (word != NULL)
	{
		if (ft_strcmp(str, word->data) == 0)
			return (TRUE);
		word = word->next;
	}
	return (FALSE);
}

void	ft_add_front_word(t_word **word, t_word *new)
{
	if (word)
	{
		if (*word)
			new->next = *word;
		*word = new;
	}
}
