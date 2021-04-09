/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_input2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolasessayan <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 15:34:38 by nicolases         #+#    #+#             */
/*   Updated: 2021/04/09 13:02:48 by nicolases        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	process_arrow_up(t_data *d, char **l)
{
	int		size;
	char	*tmp;

	size = get_size_hist(d->hist);
	if (size > 0)
	{
		if (d->hc == 0 && d->ts == 0)
		{
			store_hist(d, *l);
			d->ts = 1;
			size = get_size_hist(d->hist);
		}
		d->hc = ft_min(d->hc + 1, size - 1);
		if (*l != NULL)
			erase_line(l);
		tmp = get_str_hist(d->hist, d->hc);
		if (tmp == NULL)
			*l = NULL;
		else
		{
			*l = ft_strdup(tmp);
			ft_putstr_fd(*l, STDIN);
		}
	}
}

void	process_arrow_down(t_data *d, char **l)
{
	char	*tmp;

	if (d->hc > 0)
	{
		d->hc = d->hc - 1;
		if (*l != NULL)
			erase_line(l);
		tmp = get_str_hist(d->hist, d->hc);
		if (tmp == NULL)
			*l = NULL;
		else
		{
			*l = ft_strdup(tmp);
			ft_putstr_fd(*l, STDIN);
		}
	}
}

int		process_input_arrows(t_data *d, char **l)
{
	int		nread;
	char	c;

	nread = read(STDIN, &c, 1);
	if (c == 91)
	{
		nread = read(STDIN, &c, 1);
		if (c == 65)
			process_arrow_up(d, l);
		else if (c == 66)
			process_arrow_down(d, l);
	}
	return (nread);
}

void	process_ctrl_d(void)
{
	status = 130;
	ft_putchar_fd('\n', STDERR);
	ft_prompt_line();
}
