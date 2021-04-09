/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 11:12:19 by adelille          #+#    #+#             */
/*   Updated: 2021/04/09 11:54:12 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_mi_error(char *command, char *text, int va_error)
{
	ft_pserc("minishell: ", RED);
	ft_pserc(command, RED);
	ft_pserc(": ", RED);
	ft_pserc(text, RED);
	ft_pserc("\n", RED);
	return (va_error);
}
