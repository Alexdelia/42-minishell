/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolasessayan <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 11:20:07 by nicolases         #+#    #+#             */
/*   Updated: 2021/04/08 14:26:54 by nicolases        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_unset(t_word *word, t_env **env)
{
	char	*str;
	int		i;

	if (word == NULL)
		return ;
	str = join_env(word);
	if (is_valid_identifier(str) == 0 || is_included(str, '=') == 1)
	{
		free(str);
		return (ft_putstr_fd("\033[1;31mNot a valid identifier\n", STDERR));
	}
	if (is_inenv(str, *env) == 1)
	{
		i = get_index_env(*env, str);
		remove_index_env(env, i);
	}
	return (free(str));
}
