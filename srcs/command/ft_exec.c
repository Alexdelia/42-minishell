/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 14:14:43 by adelille          #+#    #+#             */
/*   Updated: 2021/04/13 16:16:18 by nicolases        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exec(char *path, char *str, t_env *env, int fd)
{
	char		**av;
	char		**envp;
	int			pid;
	struct stat	stats;
	int			exec_status;
	char		c;
	/*int		pfd[2];*/

	exec_status = 0;
	c = 'a';
	/*pipe(pfd);*/
	if (stat(path, &stats) == -1)
		return (ft_mi_error(path, "No such file or directory", 127));
	envp = etoa(env);
	av = ft_split(str, ' ');
	pid = fork();
	if (pid == 0)
	{
		/*dup2(pfd[1], STDERR);*/
		execve(path, av, envp);
	}
	else
  {
		while (c != 'q')
		{
			read(STDIN, &c, 1);
			if (c == 'k')
				kill(pid, 1);
			ft_putstr_fd("HELLO\n", STDOUT);
		}
		ft_putstr_fd("EXIT LOOP\n", STDOUT);
		waitpid(pid, &exec_status, 0);
		/*char BUFF[5];
		read(pfd[0], BUFF, 4);
		printf("pid: %d\nexec_status: %d\nBUFF: %s\n", pid, exec_status, BUFF);*/
		free_tab(envp);
		free_tab(av);
	}
	if (fd != STDOUT && fd != STDIN)
		close(fd);
	if (exec_status <= 255)
		ft_mi_error(path, "run into an unexpected error", 0);
	return ((exec_status <= 255 ? exec_status : exec_status / 256));
}
