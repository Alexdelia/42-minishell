/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_statable.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 18:51:00 by adelille          #+#    #+#             */
/*   Updated: 2021/04/09 19:50:54 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#define BIN_PATH "/usr/bin/"

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

int			ft_statable(t_word **word)
{
	char		*bin_path;
	int			i;
	struct stat	stats;

	bin_path = (char *)malloc(sizeof(*bin_path)
			* (ft_strlen(BIN_PATH) + ft_strlen((*word)->data) + 1));
	i = ft_mi_strcpy(bin_path, BIN_PATH, 0);
	i = ft_mi_strcpy(bin_path, (*word)->data, i);
	bin_path[i] = '\0';
	if (stat(bin_path, &stats) == -1)
	{
		free(bin_path);
		return (FALSE);
	}
	ft_free_one_word((*word));
	(*word) = ft_new_word(bin_path);
	free(bin_path);
	return (TRUE);
}
