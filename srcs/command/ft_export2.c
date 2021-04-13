/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolasessayan <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 18:57:43 by nicolases         #+#    #+#             */
/*   Updated: 2021/04/13 09:28:56 by nicolases        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		print_declare_x(t_env *env, int fd)
{
	while (env != NULL)
	{
		ft_putstr_fd("declare -x ", fd);
		ft_putstr_fd(env->name, fd);
		ft_putstr_fd("=", fd);
		ft_putstr_fd(env->data, fd);
		ft_putstr_fd("\n", fd);
		env = env->next;
	}
	if (fd != STDOUT)
		close(fd);
	return (0);
}

char	*join_env(t_word *word)
{
	char	*str;
	char	*tmp;

	str = ft_strdup(word->data);
	while (word->next != NULL)
	{
		tmp = str;
		str = ft_strjoin(tmp, word->next->data);
		free(tmp);
		word = word->next;
	}
	return (str);
}

int		is_valid_identifier(char *str)
{
	if (str[0] == '\0')
		return (0);
	if (is_included(str, '-') ||
		is_included(str, '~') ||
		is_included(str, '.') ||
		is_included(str, '^') ||
		is_included(str, '+') ||
		is_included(str, '{') ||
		is_included(str, '}') ||
		is_included(str, '$') ||
		is_included(str, '*') ||
		is_included(str, '#') ||
		is_included(str, '@') ||
		is_included(str, ' ') ||
		is_included(str, '!'))
		return (0);
	if (ft_isdigit(str[0]))
		return (0);
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
