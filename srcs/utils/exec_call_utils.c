/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_call_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolasessayan <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 12:57:41 by nicolases         #+#    #+#             */
/*   Updated: 2021/04/25 14:20:45 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int			**init_pfd(int c)
{
	int i;
	int **pfd;

	pfd = malloc(sizeof(*pfd) * c);
	i = 0;
	while (i < c)
	{
		pfd[i] = malloc(sizeof(**pfd) * 2);
		i++;
	}
	return (pfd);
}

void		free_pfd(int **pfd, int c)
{
	int i;

	i = 0;
	while (i < c)
	{
		free(pfd[i]);
		i++;
	}
	free(pfd);
}
