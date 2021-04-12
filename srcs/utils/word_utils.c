/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 07:08:50 by adelille          #+#    #+#             */
/*   Updated: 2021/04/12 16:31:18 by nicolases        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_word	*ft_new_word(char *str)
{
	t_word	*new;

	new = malloc(sizeof(t_word));
	new->data = ft_strdup(str);
	new->next = NULL;
	return (new);
}

t_word	*ft_get_last_word(t_word *word)
{
	if (word == NULL)
		return (word);
	while (word->next != NULL)
		word = word->next;
	return (word);
}

void	ft_add_back_word(t_word **word, t_word *new)
{
	t_word	*l;

	l = ft_get_last_word(*word);
	if (l != NULL)
		l->next = new;
	else
		*word = new;
}

void	ft_free_one_word(t_word *word)
{
	free(word->data);
	word->data = NULL;
	word->next = NULL;
	free(word);
	word = NULL;
}

void	ft_free_all_word(t_word *word)
{
	t_word	*t;

	while (word != NULL)
	{
		t = word;
		word = t->next;
		ft_free_one_word(t);
	}
}
