/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 14:14:43 by adelille          #+#    #+#             */
/*   Updated: 2021/04/09 17:16:21 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <string.h>
#include <errno.h>

int	ft_exec(char *path, char *str, t_env *env, int fd)
{
	char		**av;
	char		**envp;
	int			pid;
	struct stat	stats;
	int			exec_status;

	exec_status = 0;
	if (stat(path, &stats) == -1)
		return (ft_mi_error(path, "No such file or directory", 127));
	envp = etoa(env);
	av = ft_split(str, ' ');
	pid = fork();
	if (pid == 0)
		execve(path, av, envp);
	else if (pid != 0)
	{
		waitpid(pid, &exec_status, 0);
		printf("pid: %d\nexec_status: %d\n", pid, exec_status);
		free_tab(envp);
		free_tab(av);
	}
	if (fd != STDOUT && fd != STDIN)
		close(fd);
	return ((exec_status <= 255 ? exec_status : exec_status / 256));
}
