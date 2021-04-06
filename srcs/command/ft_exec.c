/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 14:14:43 by adelille          #+#    #+#             */
/*   Updated: 2021/03/31 14:24:41 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exec(const char *path, t_word word, t_env env, int fd)
{
	char	av[16][PATH_LEN];
	char	*envp;
	int		i;
	int		y;
	int		pid;
	char	c;

	pid = fork();
	if (pid == 0)
	{
		y = 0;
		while(word)
		{
			i = 0;
			while (word->data[i])
			{
				av[y][i] = word->data[i];
				i++;
			}
			y++;
			word = word.next;
		}
		// find a way to get envp back;
		execve(path, av, envp);
	}
	else if (pid != 0)
	{
		if (read(STDIN, &c, 1) != -1 && c == 28)
			kill(pid, SIGKILL);
		wait(NULL);
	}
	if (fd != STDOUT || fd != STDIN)
		close(fd);
	return (0);
}
