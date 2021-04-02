/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hist_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nessayan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 10:13:03 by nessayan          #+#    #+#             */
/*   Updated: 2021/04/02 15:59:13 by nicolases        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_hist	*new_hist(char *str)
{
	t_hist	*new;

	new = malloc(sizeof(t_hist));
	if (str == NULL)
		new->data = NULL;
	else
		new->data = ft_strdup(str);
	new->next = NULL;
	return (new);
}

void	add_front_hist(t_hist **hist, t_hist *new)
{
	new->next = *hist;
	*hist = new;
}

void	store_hist(t_data *d, char *l)
{
	if (d->hist == NULL)
		d->hist = new_hist(l);
	else
		add_front_hist(&d->hist, new_hist(l));
}

void	free_one_hist(t_hist *hist)
{
	if (hist->data != NULL)
	{
		free(hist->data);
		hist->data = NULL;
	}
	hist->next = NULL;
	free(hist);
	hist = NULL;
}
