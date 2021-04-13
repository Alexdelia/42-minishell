/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolasessayan <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 14:19:15 by nicolases         #+#    #+#             */
/*   Updated: 2021/04/13 10:42:23 by nicolases        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	etoa_utils(t_env *env, char **a, int i)
{
	int	j;
	int	k;

	j = 0;
	while (j < (int)ft_strlen(env->name))
	{
		a[i][j] = env->name[j];
		j++;
	}
	a[i][j] = '=';
	j++;
	k = 0;
	while (j < (int)(ft_strlen(env->name) + ft_strlen(env->data) + 1))
	{
		a[i][j] = env->data[k];
		k++;
		j++;
	}
	a[i][j] = '\0';
}

char	**etoa(t_env *env)
{
	char	**a;
	int		l;
	int		i;

	l = get_size_env(env);
	a = malloc(sizeof(*a) * (l + 1));
	i = 0;
	while (env != NULL)
	{
		l = ft_strlen(env->name) + ft_strlen(env->data);
		a[i] = malloc(sizeof(**a) * l + 2);
		etoa_utils(env, a, i);
		env = env->next;
		i++;
	}
	a[i] = NULL;
	return (a);
}
