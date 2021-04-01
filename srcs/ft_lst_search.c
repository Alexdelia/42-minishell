/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_search.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 18:13:42 by adelille          #+#    #+#             */
/*   Updated: 2021/03/31 15:20:33 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_env_search(char *str, t_env *env)
{
	t_env	*head;

	head = env;
	while (env != NULL)
	{
		if (ft_strcmp(str, env->name) == 0)
			return (env->data);
		env = env->next;
	}
	env = head;
	return (NULL);
}

int		ft_word_search(char *str, t_word *word)
{
	t_word	*head;

	head = word;
	while (word != NULL)
	{
		if (ft_strcmp(str, word->data) == 0)
			return (TRUE);
		word = word->next;
	}
	word = head;
	return (FALSE);
}
