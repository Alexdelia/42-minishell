/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_word_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 06:51:14 by adelille          #+#    #+#             */
/*   Updated: 2021/04/08 13:56:19 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int		ft_stop(char *str, int stop)
{
	int	i;

	i = 0;
	while (stop > 0)
	{
		if (str[i] && (str[i] == ';' || str[i] == '|' || str[i] == '>'
			|| str[i] == '<'))
		{
			if (str[i] == '>' && str[i + 1] && str[i + 1] == '>')
				i++;
			stop--;
		}
		i++;
		if (str[i] == ' ')
			i++;
	}
	return (i);
}

static t_word	*ft_error_ml(t_word **word)
{
	ft_pserc("Error: multiligne\n", RED);
	ft_free_all_word(*word);
	return (NULL);
}

t_word			*ft_word_split(t_env *env, char *str, int stop)
{
	t_word	*word;
	int		i;

	i = ft_stop(str, stop);
	i = ft_cmd(&word, env, str, i);
	if (i < 0)
		return (ft_error_ml(&word));
	i = ft_content(&word, env, str, i);
	if (i < 0)
		return (ft_error_ml(&word));
	return (word);
}
