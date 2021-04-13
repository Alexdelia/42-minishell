/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 14:14:43 by adelille          #+#    #+#             */
/*   Updated: 2021/04/13 18:13:30 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exec(t_word *word, t_env *env, int fd)
{
	char		**av;
	char		**envp;
	int			pid;
	struct stat	stats;
	int			exec_status;
	/*int		pfd[2];*/

	exec_status = 0;
	/*pipe(pfd);*/
	if (stat(word->data, &stats) == -1)
		return (ft_mi_error(word->data, "No such file or directory", 127));
	envp = etoa(env);
	if (word->next != NULL)
		av = ft_split(word->next->data, ' ');
	else
		av = ft_split("", ' ');
	pid = fork();
	if (pid == 0)
	{
		/*dup2(pfd[1], STDERR);*/
		execve(word->data, av, envp);
	}
	else
	{
		waitpid(pid, &exec_status, 0);
		/*char BUFF[5];
		read(pfd[0], BUFF, 4);
		printf("pid: %d\nexec_status: %d\nBUFF: %s\n", pid, exec_status, BUFF);*/
		free_tab(envp);
		free_tab(av);
	}
	if (fd != STDOUT && fd != STDIN)
		close(fd);
	if (exec_status != 0 && exec_status < 256)
		ft_mi_error(word->data, "run into an unexpected error", 0);
	return ((exec_status < 256 ? exec_status : exec_status / 256));
}
