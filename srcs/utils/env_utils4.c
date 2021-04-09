/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolasessayan <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 14:19:15 by nicolases         #+#    #+#             */
/*   Updated: 2021/04/09 14:52:09 by nicolases        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**etoa(t_env *env)
{
	char	**a;
	int		l;
	int		i;
	int		j;
	int		k;

	l = get_size_env(env);
	a = malloc(sizeof(*a) * (l + 1));
	i = 0;
	while (env != NULL)
	{
		l = ft_strlen(env->name) + ft_strlen(env->data);
		a[i] = malloc(sizeof(**a) * l + 2);
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
		env = env->next;
		i++;
	}
	a[i] = NULL;
	return (a);
}
