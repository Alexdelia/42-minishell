/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolasessayan <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 11:31:01 by nicolases         #+#    #+#             */
/*   Updated: 2021/04/13 12:13:47 by nicolases        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_strdigit(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		if (ft_isdigit(str[i]) == 0 && str[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

int	ft_exit(t_data *d)
{
	int		ret;
	char	**split;

	if (is_strdigit(d->word->next->data) == 0)
	{
		d->exit = 1;
		ft_putstr_fd("exit\n", STDOUT);
		return (ft_mi_error("exit", "numeric argument required", 2));
	}
	split = ft_split2(d->word->next->data, ' ');
	if (ft_tablen(split) > 1)
	{
		free_tab(split);
		return (ft_mi_error("exit", "too many arguments", 1));
	}
	d->exit = 1;
	ret = ft_atoi(split[0]);
	free_tab(split);
	ft_putstr_fd("exit\n", STDOUT);
	return (ret);
}
