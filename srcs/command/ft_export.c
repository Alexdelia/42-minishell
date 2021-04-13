/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolasessayan <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 12:06:30 by nicolases         #+#    #+#             */
/*   Updated: 2021/04/13 09:30:30 by nicolases        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	process_name_data(t_env **env, char **split)
{
	char	*tmp;
	t_env	*elm;

	if (is_inenv(split[0], *env))
	{
		elm = get_env_by_name(split[0], *env);
		tmp = ft_strjoin(ft_env_search(split[0], *env), split[2]);
		free(elm->data);
		if (split[1][0] != '+')
			elm->data = ft_strdup(split[2]);
		else
			elm->data = ft_strdup(tmp);
		free(tmp);
	}
	else
	{
		elm = malloc(sizeof(*elm));
		elm->name = ft_strdup(split[0]);
		elm->data = ft_strdup(split[2]);
		elm->next = NULL;
		add_back_env(env, elm);
	}
}

int		no_equal_case(char *str)
{
	if (is_valid_identifier(str) == 1)
		return (0);
	else
	{
		ft_mi_error("export", "not a valid identifier", 1);
		return (1);
	}
}

int		unvalid_case(char **split)
{
	ft_mi_error("export", "not a valid identifier", 1);
	free_tab(split);
	return (1);
}

int		treat_one_arg(char *str, int i, t_env **env, int fd)
{
	char **split;

	if (str[0] == '\0' || str[0] == '#')
	{
		if (i == 0)
			return (print_declare_x(*env, fd));
		else
			return (0);
	}
	if (is_included(str, '=') == 0)
		return (no_equal_case(str));
	split = split_export(str);
	if (is_valid_identifier(split[0]) == 0)
		return (unvalid_case(split));
	else
		process_name_data(env, split);
	free_tab(split);
	return (0);
}

int		ft_export(t_word *word, t_env **env, int fd)
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
		if ((tmp = treat_one_arg(split[i], i, env, fd)) != 0)
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
