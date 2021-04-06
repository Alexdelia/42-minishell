/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hist_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolasessayan <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 18:32:39 by nicolases         #+#    #+#             */
/*   Updated: 2021/04/06 15:22:56 by nicolases        ###   ########.fr       */
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

int		get_size_hist(t_hist *hist)
{
	int	i;

	i = 0;
	while (hist != NULL)
	{
		i++;
		hist = hist->next;
	}
	return (i);
}

char	*get_str_hist(t_hist *hist, int index)
{
	int	i;

	i = 0;
	while (i != index)
	{
		hist = hist->next;
		i++;
	}
	return (hist->data);
}

void	pop_hist(t_data *d)
{
	t_hist *tmp;

	tmp = d->hist;
	d->hist = d->hist->next;
	free_one_hist(tmp);
}
