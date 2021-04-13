/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_statable.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 18:51:00 by adelille          #+#    #+#             */
/*   Updated: 2021/04/13 17:55:18 by adelille         ###   ########.fr       */
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

int			ft_statable(t_word **word, t_env *env)
{
	char		*bin_path;
	char		*va_path;
	t_parser	p;
	t_word		*tmp;
	struct stat	stats;

	p.i = 0;
	p.y = 0;
	va_path = ft_env_search("PATH", env);
	while (va_path[p.i])
	{
		bin_path = (char *)malloc(sizeof(*bin_path)
				* (ft_strlen_until_c(va_path, ':', p.i)
				+ ft_strlen((*word)->data) + 2));
		p.y = 0;
		/*ft_ps("va_path[p.i] =");
		ft_ps(&va_path[p.i]);
		ft_ps("\np.i = ");
		ft_putnbr_fd(p.i, STDOUT);
		ft_ps("\n");*/
		ft_mi_strcpy(&p, bin_path, va_path,
				ft_strlen_until_c(va_path, ':', p.i));
		ft_mi_s_strcpy(&p, bin_path, (*word)->data);
		bin_path[p.y] = '\0';
		if (stat(bin_path, &stats) == -1)
			free(bin_path);
		else
		{
			ft_add_front_word(word, ft_new_word(bin_path));
			tmp = (*word)->next;
			(*word)->next = (*word)->next->next;
			ft_free_one_word(tmp);
			free(bin_path);
			ft_ps("OUT\n");
			return (TRUE);
		}
		p.i = ft_strlen_until_c(va_path, ':', p.i);
		if (va_path[p.i] && va_path[p.i] == ':')
			p.i++;
	}
	return (FALSE);
}
