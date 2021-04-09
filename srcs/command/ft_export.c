/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolasessayan <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 12:06:30 by nicolases         #+#    #+#             */
/*   Updated: 2021/04/09 15:31:09 by nicolases        ###   ########.fr       */
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
	{
		free(str);
		return (0);
	}
	else
	{
		ft_mi_error("export", "not a valid identifier", 1);
		free(str);
		return (1);
	}
}

int		unvalid_case(char *str, char **split)
{
	ft_mi_error("export", "not a valid identifier", 1);
	free(str);
	free_tab(split);
	return (1);
}

char	**split_export(char *str)
{
	char	**split;
	int		l;
	int		i;
	int		p;

	l = ft_strlen(str);
	split = malloc(sizeof(*split) * 4);
	i = 0;
	while (str[i] != '=')
		i++;
	p = 0;
	if (i != 0 && str[i - 1] == '+')
		p = 1;
	if (i > 0)
		split[0] = ft_strdup2(str, 0, i - p);
	else
		split[0] = ft_strdup("");
	if (p == 1)
		split[1] = ft_strdup("+");
	else
		split[1] = ft_strdup("");
	split[2] = ft_strdup2(str, i + 1, l);
	split[3] = NULL;
	return (split);
}

int		ft_export(t_word *word, t_env **env, int fd)
{
	char	*str;
	char	**split;

	str = NULL;
	if (word == NULL)
		return (print_declare_x(*env, fd));
	str = join_env(word);
	if (str[0] == '\0' || str[0] == '#')
	{
		free(str);
		return (print_declare_x(*env, fd));
	}
	if (is_included(str, '=') == 0)
		return (no_equal_case(str));
	split = split_export(str);
	if (is_valid_identifier(split[0]) == 0)
		return (unvalid_case(str, split));
	else
		process_name_data(env, split);
	free(str);
	free_tab(split);
	return (0);
}
