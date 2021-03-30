/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_search.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 18:13:42 by adelille          #+#    #+#             */
/*   Updated: 2021/03/30 18:24:39 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_env_search(char *str, t_env env)
{
	while (env)
	{
		if (ft_strcmp(str, env.name) == 0)
			return (env.data);
		env = env.next;
	}
	return ("\0");
}

int		ft_word_search(t_word word, char *str)
{
	while (word)
	{
		if (ft_strcmp(str, word.data) == 0)
			return (TRUE);
		word = word.next;
	}
	return (FALSE);
}
