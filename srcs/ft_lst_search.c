/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_search.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 18:13:42 by adelille          #+#    #+#             */
/*   Updated: 2021/04/01 12:56:46 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_env_search(char *str, t_env *env)
{
	if (str[0] != '$')
		return (str);
	while (env != NULL)
	{
		if (ft_strcmp(&str[1], env->name) == 0)
			return (env->data);
		env = env->next;
	}
	return (str);
}

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
