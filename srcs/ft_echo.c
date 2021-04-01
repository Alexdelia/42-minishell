/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 17:41:22 by adelille          #+#    #+#             */
/*   Updated: 2021/04/01 12:56:04 by adelille         ###   ########.fr       */
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

static int	ft_has_n(t_word *word)
{
	while (word)
	{
		if (ft_is_n(word->data) == TRUE)
			return (TRUE);
		word = word->next;
	}
	return (FALSE);
}

static void	ft_echo_env_convert(int fd, char *str, t_env *env)
{
	ft_putstr_fd(ft_env_search(&str[1], env), fd);
}

int			ft_echo(int fd, t_word *word, t_env *env)
{
	t_word	*head;

	head = word;
	while (word)
	{
		if (word->data[0] == '$')
			ft_echo_env_convert(fd, word->data, env);
		else if (ft_is_n(word->data) == FALSE)
			ft_putstr_fd(word->data, fd);
		word = word->next;
	}
	word = head;
	//ft_lstclear(head, free);
	if (ft_has_n(word) == FALSE)
		ft_putstr_fd("\n", fd);
	if (fd != STDOUT)
		close(fd);
	return (0);
}
