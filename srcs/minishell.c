/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolasessayan <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 17:24:02 by nicolases         #+#    #+#             */
/*   Updated: 2021/04/16 14:18:37 by nicolases        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		process_input(t_data *d, char **l)
{
	int		nread;
	char	c;

	nread = read(STDIN, &c, 1);
	if (ft_isprint(c) == 1)
		process_input_printable(l, c);
	else if (c == 127 && *l != NULL)
		process_input_del(l);
	else if (c == 10)
		process_input_newline(d, l);
	else if (c == 27)
		process_input_arrows(d, l);
	else if (c == 3)
		process_ctrl_c();
	else if (c == 4 && *l == NULL)
		process_ctrl_d(d);
	if (c == 10 || c == 3)
	{
		free(*l);
		*l = NULL;
	}
	return (nread);
}

void	free_all(t_data *d)
{
	free_all_env(d->env);
	free_all_hist(d->hist);
}

void	enable_raw_mode(t_data *d)
{
	struct termios raw;

	raw = d->orig_termios;
	raw.c_lflag &= ~(ECHO | ICANON | ISIG);
	tcsetattr(STDIN, TCSAFLUSH, &raw);
}

void	init_data(t_data *d, char **env)
{
	d->hist = NULL;
	d->env = init_env(env);
	d->word = NULL;
	d->exit = 0;
	d->hc = 0;
	d->ts = 0;
	g_status = 0;
	tcgetattr(STDIN, &(d->orig_termios));
}

int		main(int ac, char **av, char **env)
{
	t_data	d;
	//char	*l;
	int		term;
	(void)ac;
	(void)av;
	if (TERMCAP && (term = init_term()) == -1)
		return (-1);
	init_data(&d, env);
	/* create the pipe */
	int pfd[2];
	if (pipe(pfd) == -1)
	{
		printf("pipe failed\n");
		return 1;
	}
	/* create the child */
	int pid;
	if ((pid = fork()) < 0)
	{
		printf("fork failed\n");
		return 2;
	}
	if (pid == 0)
	{
		/* child */
		close(pfd[1]); /* close the unused write side */
		dup2(pfd[0], 0); /* connect the read side with stdin */
		close(pfd[0]); /* close the read side */
		/* execute the process (wc command) */
		ft_word_split(&d, "/usr/bin/wc", 0);
		ft_parse_exec(d.word, &d, STDOUT);
		ft_free_all_word(d.word);
	}
	else
	{
		/* parent */
		close(pfd[0]); /* close the unused read side */
		dup2(pfd[1], 1); /* connect the write side with stdout */
		close(pfd[1]); /* close the write side */
		/* execute the process (ls command) */
		ft_word_split(&d, "/bin/ls", 0);
		ft_parse_exec(d.word, &d, STDOUT);
		ft_free_all_word(d.word);
	}
	free_all(&d);
	tcsetattr(STDIN, TCSAFLUSH, &(d.orig_termios));
	exit(g_status);
}
