/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_statable.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 18:51:00 by adelille          #+#    #+#             */
/*   Updated: 2021/04/13 20:29:16 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	ft_mi_strcpy(t_parser *p, char *dst, const char *src, int end)
{
	while (src[p->i] && p->i < end)
	{
		dst[p->y] = src[p->i];
		p->i++;
		p->y++;
	}
}

static void	ft_mi_s_strcpy(t_parser *p, char *dst, const char *src)
{
	int	i;

	dst[p->y] = '/';
	p->y++;
	i = 0;
	while (src[i])
	{
		dst[p->y] = src[i];
		i++;
		p->y++;
	}
}

static int	ft_strlen_until_c(char *str, char c, int start)
{
	while (str[start] && str[start] != c)
		start++;
	return (start);
}

static char	*ft_create_bin_path(t_word **word, t_parser *p, char *va_path)
{
	char	*bin_path;

	bin_path = (char *)malloc(sizeof(*bin_path)
			* (ft_strlen_until_c(va_path, ':', p->i)
			+ ft_strlen((*word)->data) + 2));
	p->y = 0;
	ft_mi_strcpy(p, bin_path, va_path,
			ft_strlen_until_c(va_path, ':', p->i));
	ft_mi_s_strcpy(p, bin_path, (*word)->data);
	bin_path[p->y] = '\0';
	return (bin_path);
}

int			ft_statable(t_word **word, t_env *env)
{
	char		*bin_path;
	char		*va_path;
	t_parser	p;
	struct stat	stats;

	p.i = 0;
	p.y = 0;
	va_path = ft_env_search("PATH", env);
	while (va_path[p.i])
	{
		bin_path = ft_create_bin_path(word, &p, va_path);
		if (stat(bin_path, &stats) == -1)
			free(bin_path);
		else
		{
			free((*word)->data);
			(*word)->data = ft_strdup(bin_path);
			free(bin_path);
			return (TRUE);
		}
		p.i = ft_strlen_until_c(va_path, ':', p.i);
		if (va_path[p.i] && va_path[p.i] == ':')
			p.i++;
	}
	return (FALSE);
}
