/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 14:14:43 by adelille          #+#    #+#             */
/*   Updated: 2021/04/15 17:25:21 by nicolases        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char		**ft_create_av(t_word *word)
{
	char	**av;
	char	*join_f;
	char	*join_e;

	join_f = ft_strjoin(word->data, " ");
	if (word->next != NULL)
		join_e = ft_strjoin(join_f, word->next->data);
	else
		join_e = ft_strdup(join_f);
	av = ft_split(join_e, ' ');
	free(join_f);
	free(join_e);
	return (av);
}

static int		return_value(int exec_status, char *bin)
{
	if (exec_status == 2)
		return (130);
	else if (exec_status == 3)
	{
		ft_putstr_fd("Quit: 3\n", STDOUT);
		return (131);
	}
	else if (exec_status == 11 || exec_status == 139)
		return (ft_mi_error(bin, "segmentation fault", 139));
	else if (exec_status != 0 && exec_status < 256)
		ft_mi_error(bin, "run into an unexpected error", 0);
	if (exec_status > 255)
		return (exec_status / 256);
	return (exec_status);
}

static	void	handle_sig(int sig)
{
	sig = 1;
}

static	void	wait_and_signal(int *exec_status, int pid)
{
	signal(SIGINT, handle_sig);
	signal(SIGQUIT, handle_sig);
	waitpid(pid, exec_status, 0);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

int				ft_exec(t_word *word, t_env *env, int fd)
{
	char		**av;
	char		**envp;
	int			pid;
	struct stat stats;
	int			exec_status;

	exec_status = 0;
	if (stat(word->data, &stats) == -1)
		return (ft_mi_error(word->data, "No such file or directory", 127));
	envp = etoa(env);
	av = ft_create_av(word);
	pid = fork();
	if (pid == 0)
		execve(word->data, av, envp);
	else
	{
		wait_and_signal(&exec_status, pid);
		free_tab(envp);
		free_tab(av);
	}
	if (fd != STDOUT && fd != STDIN)
		close(fd);
	return (return_value(exec_status, word->data));
}
