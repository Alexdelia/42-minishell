/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_statable.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 18:51:00 by adelille          #+#    #+#             */
/*   Updated: 2021/04/12 08:33:54 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	ft_mi_strcpy(char *dst, const char *src, int i)
{
	int	j;

	j = 0;
	while (src[j] && i >= 0)
	{
		dst[i] = src[j];
		i++;
		j++;
	}
	return (i);
}

static int	ft_strlen_until_c(char *str, char c, int start)
{
	while (str[start] && str[start] != c)
		start++;
	return (start);
}

int			ft_statable(t_word **word, t_env *env)
{
	char		*bin_path;
	char		*va_path;
	int			i;
	int			y;
	struct stat	stats;

	i = 0;
	y = 0;
	va_path = ft_env_search("PATH", env);
	while (va_path[i])
	{
		bin_path = (char *)malloc(sizeof(*bin_path)
				* ((ft_strlen_until_c(va_path, ':', i) - y)
				+ ft_strlen((*word)->data) + 1));
		y = 0;
		y = ft_mi_strcpy(bin_path, &va_path[i], 0);
		y = ft_mi_strcpy(bin_path, (*word)->data, i);
		bin_path[y] = '\0';
		if (stat(bin_path, &stats) == -1)
			free(bin_path);
		else
		{
			ft_free_one_word((*word));
			(*word) = ft_new_word(bin_path);
			free(bin_path);
			return (TRUE);
		}
		y = i;
		i = ft_strlen_until_c(va_path, ':', i) + 1;
	}
	return (FALSE);
}
