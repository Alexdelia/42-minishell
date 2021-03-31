/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolasessayan <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 18:32:39 by nicolases         #+#    #+#             */
/*   Updated: 2021/03/31 11:05:24 by nessayan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_all_hist(t_hist *hist)
{
	t_hist *t;

	while (hist != NULL)
	{
		t = hist;
		hist = t->next;
		free_one_hist(t);
	}
}

void	print_hist(t_hist *hist)
{
	while (hist != NULL)
	{
		printf("%s\n", hist->data);
		hist = hist->next;
	}
}
