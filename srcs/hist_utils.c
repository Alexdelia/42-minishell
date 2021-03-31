/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hist_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nessayan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 10:13:03 by nessayan          #+#    #+#             */
/*   Updated: 2021/03/31 11:05:34 by nessayan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_hist	*new_hist(char *str)
{
	t_hist	*new;

	new = malloc(sizeof(t_hist));
	new->data = ft_strdup(str);
	new->next = NULL;
	return (new);
}

t_hist	*get_last_hist(t_hist *hist)
{
	if (hist == NULL)
		return (hist);
	while (hist->next != NULL)
		hist = hist->next;
	return (hist);
}

void	add_back_hist(t_hist **hist, t_hist *new)
{
	t_hist	*l;

	l = get_last_hist(*hist);
	if (l != NULL)
		l->next = new;
	else
		*hist = new;
}

void	store_hist(t_data *d, char *l)
{
	if (d->hist == NULL)
		d->hist = new_hist(l);
	else
		add_back_hist(&d->hist, new_hist(l));
}

void	free_one_hist(t_hist *hist)
{
	free(hist->data);
	hist->data = NULL;
	hist->next = NULL;
	free(hist);
	hist = NULL;
}
