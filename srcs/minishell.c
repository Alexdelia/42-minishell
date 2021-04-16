/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolasessayan <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 17:24:02 by nicolases         #+#    #+#             */
/*   Updated: 2021/04/16 17:29:38 by nicolases        ###   ########.fr       */
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
	char	*l;
	int		term;

	if (TERMCAP && (term = init_term()) == -1)
		return (-1);
	init_data(&d, env);
	if (ac == 1)
	{
		enable_raw_mode(&d);
		l = NULL;
		ft_prompt_line();
		while (d.exit == 0)
			process_input(&d, &l);
	}
	else if (ac == 3 && ft_strcmp(av[1], "-c") == 0)
		ft_exec_command(av[2], &d);
	else
		ft_mi_error("main", "wrong argument(s)", 1);
	free_all(&d);
	tcsetattr(STDIN, TCSAFLUSH, &(d.orig_termios));
	exit(g_status);
}
