/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 17:41:22 by adelille          #+#    #+#             */
/*   Updated: 2021/04/07 14:01:08 by nicolases        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	ft_is_n(char *str)
{
	int	i;

	i = 1;
	if (str[0] && str[1] && str[0] == '-' && str[1] == 'n')
	{
		while (str[i])
		{
			if (str[i] != 'n')
				return (FALSE);
			i++;
		}
		return (TRUE);
	}
	return (FALSE);
}

int			ft_echo(int fd, t_word *word)
{
	t_word	*head;

	if (!word)
	{
		ft_putstr_fd("\n", fd);
		return (1);
	}
	head = word;
	while (ft_is_n(word->data))
		word = word->next;
	while (word)
	{
		ft_putstr_fd(word->data, fd);
		word = word->next;
		if (word)
			ft_putstr_fd(" ", fd);
	}
	word = head;
	//ft_lstclear(head, free);
	if (ft_is_n(word->data) == FALSE)
		ft_putstr_fd("\n", fd);
	if (fd != STDOUT)
		close(fd);
	return (0);
}
