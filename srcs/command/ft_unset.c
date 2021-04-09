/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolasessayan <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 11:20:07 by nicolases         #+#    #+#             */
/*   Updated: 2021/04/09 13:10:28 by nicolases        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_unset(t_word *word, t_env **env)
{
	char	*str;
	int		i;

	if (word == NULL)
		return (0);
	str = join_env(word);
	if (str[0] == '\0')
	{
		free(str);
		return (0);
	}
	if (is_valid_identifier(str) == 0 || is_included(str, '=') == 1)
	{
		ft_mi_error("unset", "not a valid identifier", 1);
		free(str);
		return (1);
	}
	if (is_inenv(str, *env) == 1)
	{
		i = get_index_env(*env, str);
		remove_index_env(env, i);
	}
	free(str);
	return (0);
}
