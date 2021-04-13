/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolasessayan <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 11:20:07 by nicolases         #+#    #+#             */
/*   Updated: 2021/04/13 10:11:28 by nicolases        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	treat_one_arg_unset(char *str, t_env **env)
{
	int		i;

	if (str[0] == '\0' || str[0] == '#')
		return (0);
	if (is_valid_identifier(str) == 0 || is_included(str, '=') == 1)
	{
		ft_mi_error("unset", "not a valid identifier", 1);
		return (1);
	}
	if (is_inenv(str, *env) == 1)
	{
		i = get_index_env(*env, str);
		remove_index_env(env, i);
	}
	return (0);
}

int	ft_unset(t_word *word, t_env **env)
{
	char	**split;
	int		i;
	int		ret;
	int		tmp;

	ret = 0;
	split = ft_split2(word->data, ' ');
	i = 0;
	while (split[i] != NULL)
	{
		if ((tmp = treat_one_arg_unset(split[i], env)) != 0)
			ret = tmp;
		if (split[i][0] == '#')
		{
			free_tab(split);
			return (ret);
		}
		i++;
	}
	free_tab(split);
	return (ret);
}
