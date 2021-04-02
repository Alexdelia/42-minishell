/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ps.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/26 13:09:31 by adelille          #+#    #+#             */
/*   Updated: 2021/04/02 10:58:01 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_ps(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	write(1, str, i);
	return (i);
}

int	ft_psc(char *str, char *color)
{
	write(1, color, ft_strlen(color));
	write(1, str, ft_strlen(str));
	write(1, DEF, ft_strlen(DEF));
	return (ft_strlen(color) + ft_strlen(str) + ft_strlen(DEF));
}

int	ft_pserc(char *str, char *color)
{
	write(2, color, ft_strlen(color));
	write(2, str, ft_strlen(str));
	write(2, DEF, ft_strlen(DEF));
	return (ft_strlen(color) + ft_strlen(str) + ft_strlen(DEF));
}
