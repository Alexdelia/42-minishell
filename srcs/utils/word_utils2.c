/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolasessayan <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 19:01:36 by nicolases         #+#    #+#             */
/*   Updated: 2021/04/07 19:01:37 by nicolases        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_word_search(char *str, t_word *word)
{
	while (word != NULL)
	{
		if (ft_strcmp(str, word->data) == 0)
			return (TRUE);
		word = word->next;
	}
	return (FALSE);
}
