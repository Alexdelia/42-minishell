/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 15:18:42 by user42            #+#    #+#             */
/*   Updated: 2021/04/07 19:35:23 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_mi_strcat(char **dst, const char *src, int y, t_env *env)
{
	int		i;
	char	*na_env;
	char	*dt_env;

	i = 0;
	na_env = (char *)malloc(sizeof(*na_env) * (ft_strlen(src) + 1));
	while (src[i + 1] && src[i + 1] != ' ' && src[i + y] != ';'
		&& src[i + 1] != '\"' && src[i + 1] != '\'')
	{
		na_env[i] = src[i + 1];
		i++;
	}
	na_env[i] = '\0';
	dt_env = ft_env_search(na_env, env);
	free(na_env);
	i = 0;
	while (dt_env[i] && y < PATH_LEN)
	{
		(*dst)[y] = dt_env[i];
		i++;
		y++;
	}
	return (y);
}
