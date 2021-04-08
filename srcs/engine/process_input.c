/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolasessayan <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 15:33:14 by nicolases         #+#    #+#             */
/*   Updated: 2021/04/08 14:05:30 by nicolases        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*append_str(char *str, char c)
{
	char	*tmp;
	int		l;
	int		i;

	if (str == NULL)
		l = 0;
	else
		l = ft_strlen(str);
	tmp = malloc(sizeof(*tmp) * (l + 2));
	i = 0;
	while (i < l)
	{
		tmp[i] = str[i];
		i++;
	}
	tmp[i] = c;
	tmp[i + 1] = '\0';
	if (str != NULL)
	{
		free(str);
		str = NULL;
	}
	return (tmp);
}

char	*pop_str(char *str)
{
	char	*tmp;
	int		l;
	int		i;

	l = ft_strlen(str);
	if (l == 1)
	{
		free(str);
		return (NULL);
	}
	tmp = malloc(sizeof(*tmp) * l);
	i = 0;
	while (i < l - 1)
	{
		tmp[i] = str[i];
		i++;
	}
	tmp[i] = '\0';
	free(str);
	str = NULL;
	return (tmp);
}

void	process_input_printable(char **l, char c)
{
	*l = append_str(*l, c);
	ft_putchar_fd(c, STDIN);
}

void	process_input_del(char **l)
{
	*l = pop_str(*l);
	put_cursor_backward(1);
}

void	process_input_newline(t_data *d, char **l)
{
	ft_putchar_fd(10, STDIN);
	if (d->ts == 1)
		pop_hist(d);
	d->hc = 0;
	d->ts = 0;
	if (*l != NULL)
	{
		store_hist(d, *l);
		ft_exec_command(*l, d);
	}
	ft_prompt_line();
}
