/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nessayan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/24 13:47:46 by nessayan          #+#    #+#             */
/*   Updated: 2021/04/12 18:28:05 by nicolases        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	ft_count(const char *str, char c)
{
	int i;
	int t;

	t = 0;
	i = 0;
	while (str[i])
	{
		while (str[i] && str[i] == c)
			i++;
		if (str[i] && str[i] != c)
		{
			t++;
			while (str[i] && str[i] != c)
				i++;
		}
	}
	return (t);
}

static char	*ft_strdup2(const char *src, int start, int end)
{
	char	*dest;
	int		l;
	int		i;

	l = end - start + 1;
	dest = malloc(sizeof(*dest) * (l + 1));
	if (dest == NULL)
		return (NULL);
	i = 0;
	while (start + i <= end)
	{
		dest[i] = src[start + i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

static void	ft_tabclear(char **tab, int n)
{
	int		i;

	i = 0;
	while (i < n)
	{
		free(tab[i]);
		tab[i] = NULL;
		i++;
	}
}

char		**ft_filltab(char **tab, char const *s, char c)
{
	int		i;
	int		j;
	int		t;

	t = -1;
	i = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] && s[i] != c)
		{
			t++;
			j = i;
			while (s[i] && s[i] != c)
				i++;
			if ((tab[t] = ft_strdup2(s, j, i - 1)) == NULL)
			{
				ft_tabclear(tab, t);
				return (NULL);
			}
		}
	}
	tab[ft_count(s, c)] = NULL;
	return (tab);
}

char		**ft_split2(char const *s, char c)
{
	char	**tab;

	if ((tab = malloc(sizeof(*tab) * (ft_count(s, c) + 1))) == NULL)
		return (NULL);
	if ((tab = ft_filltab(tab, s, c)) == NULL)
		free(tab);
	return (tab);
}
