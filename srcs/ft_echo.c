/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 17:41:22 by adelille          #+#    #+#             */
/*   Updated: 2021/03/31 14:40:31 by nessayan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_echo_env_convert(int fd, char *str, t_env *env)
{
	char	*to_write;

	to_write = ft_env_search(str, *env);
	write(fd, to_write, ft_strlen(to_write));
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
			write(fd, word->data, ft_strlen(word->data));
		word = word->next;
	}
	word = head;
	//ft_lstclear(head, free);
	if (ft_word_search(*word, "-n") == FALSE)
		ft_putstr_fd("\n", STDOUT);
	return (0);
}
