/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 17:41:22 by adelille          #+#    #+#             */
/*   Updated: 2021/03/31 15:09:18 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_echo_env_convert(int fd, char *str, t_env *env)
{
	ft_putstr_fd(ft_env_search(str, *env), fd);
}

int			ft_echo(int fd, t_word *word, t_env *env)
{
	t_word	*head;

	head = word;
	while (word)
	{
		if (word->data[0] == '$' && ft_strcmp(word->data, "$") != 0)
			ft_echo_env_convert(fd, word->data, env);
		else if (ft_strcmp(word->data, "-n") != 0)
			ft_putstr_fd(word->data, fd);
		word = word->next;
	}
	word = head;
	//ft_lstclear(head, free);
	if (ft_word_search(*word, "-n") == FALSE)
		ft_putstr_fd("\n", fd);
	if (fd != STDOUT)
		close(fd);
	return (0);
}