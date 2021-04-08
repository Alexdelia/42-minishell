/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolasessayan <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 17:24:02 by nicolases         #+#    #+#             */
/*   Updated: 2021/04/08 13:59:30 by nicolases        ###   ########.fr       */
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
	{
		ft_putchar_fd('\n', STDERR);
		ft_prompt_line();
	}
	else if (c == 4)
		d->exit = 1;
	if (c == 10 || c == 3 || c == 4)
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

void	enable_raw_mode(void)
{
	struct termios raw;

	tcgetattr(STDIN, &orig_termios);
	raw = orig_termios;
	raw.c_lflag &= ~(ECHO | ICANON | ISIG);
	tcsetattr(STDIN, TCSAFLUSH, &raw);
}

void	init_data(t_data *d, char **env)
{
	d->hist = NULL;
	d->env = init_env(env);
	d->exit = 0;
	d->hc = 0;
	d->ts = 0;
}

int		main(int ac, char **av, char **env)
{
	t_data	d;
	char	*l;

	/*(void)ac;*/
	/*(void)av;*/
	init_data(&d, env);
	/*print_env(d.env);
	remove_index_env(&(d.env), 0);
	printf("8888888888888888888888\n");
	print_env(d.env);*/
	if (ac == 1)
	{
		enable_raw_mode();
		l = NULL;
		ft_prompt_line();
		while (d.exit == 0)
			process_input(&d, &l);
	}
	else if (ac == 3 && ft_strcmp(av[1], "-c") == 0)
		ft_exec_command(av[2], d.env);
	else
		ft_putstr_fd("\033[0;31mWrong arguments - Please retry\n", STDERR);
	free_all(&d);
	tcsetattr(STDIN, TCSAFLUSH, &orig_termios);
}
