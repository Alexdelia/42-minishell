/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 15:18:42 by user42            #+#    #+#             */
/*   Updated: 2021/04/08 14:13:23 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*ft_f_mi_strcat(const char *src)
{
	int		i;
	char	*na_env;

	i = 0;
	na_env = (char *)malloc(sizeof(*na_env) * (ft_strlen(src) + 1));
	while (src[i + 1] && src[i + 1] != ' ' && src[i + 1] != ';'
		&& src[i + 1] != '\"' && src[i + 1] != '\'' && src[i + 1] != '=')
	{
		na_env[i] = src[i + 1];
		i++;
	}
	na_env[i] = '\0';
	return (na_env);
}

static int	ft_copy(char **dst, int y, char *dt_env)
{
	int i;

	i = 0;
	while (dt_env[i] && y < PATH_LEN)
	{
		(*dst)[y] = dt_env[i];
		i++;
		y++;
	}
	return (y);
}

int			ft_mi_strcat(char **dst, const char *src, int y, t_env *env)
{
	int		i;
	int		equal;
	char	*na_env;
	char	*dt_env;

	equal = FALSE;
	if (src[0] && src[0] == '$' && (!src[1] || src[1] == '='))
	{
		(*dst)[y] = '$';
		if (src[1] && src[1] == '=')
			equal = TRUE;
		else
			return (1);
	}
	else
	{
		i = 0;
		while (src[i + 1] && src[i + 1] != ' ' && src[i + y] != ';'
			&& src[i + 1] != '\"' && src[i + 1] != '\'' && src[i + 1] != '='
			&& src[i + 1] != '|' && src[i + 1] != '>' && src[i + 1] != '<')
			i++;
		if (src[i + 1] && src[i + 1] == '=')
			equal = TRUE;
		na_env = ft_f_mi_strcat(src);
		dt_env = ft_env_search(na_env, env);
		free(na_env);
		y = ft_copy(dst, y, dt_env);
	}
	return (y);
}
