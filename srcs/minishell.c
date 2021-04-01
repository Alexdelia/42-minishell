/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolasessayan <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 17:24:02 by nicolases         #+#    #+#             */
/*   Updated: 2021/04/01 18:12:24 by nessayan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		init_term(void)
{
	int		ret;
	char	*term_type;

	term_type = getenv("TERM");
	if (term_type == NULL)
	{
		ft_putstr_fd("TERM must be set (see 'env').\n", STDERR);
		return (-1);
	}
	ret = tgetent(NULL, term_type);
	if (ret == -1)
	{
		ft_putstr_fd("Could not access to the termcap database.\n", STDERR);
		return (-1);
	}
	else if (ret == 0)
	{
		ft_putstr_fd("Terminal type is not defined.\n", STDERR);
		return (-1);
	}
	return (0);
}

void	disable_raw_mode(void)
{
	tcsetattr(STDIN, TCSAFLUSH, &orig_termios);
}

void	enable_raw_mode(void)
{
	struct termios raw;

	tcgetattr(STDIN, &orig_termios);
	atexit(disable_raw_mode);
	raw = orig_termios;
	raw.c_lflag &= ~(ICANON | ISIG);
	tcsetattr(STDIN, TCSAFLUSH, &raw);
}

int		ft_putchar(int c)
{
	write(1, &c, 1);
	return (1);
}

void	put_cursor_backward(void)
{
	char *cap;

	cap = tgetstr("le", NULL);
	tputs(cap, STDOUT, ft_putchar);
}

void	free_all(t_data *d)
{
	free_all_env(d->env);
	free_all_hist(d->hist);
}

void	init_data(t_data *d, char **env)
{
	d->hist = NULL;
	d->env = init_env(env);
	d->exit = 0;
}

void	launch_minishell(t_data *d, char *l)
{
	if (l[0] != '\0')
		store_hist(d, l);
	if (l[0] == '\0')
		d->exit = 1;
	ft_exec_command(l, d->env);
}

int		main(int ac, char **av, char **env)
{
	t_data	d;
	int		term;
	char	*l;

	init_data(&d, env);
	enable_raw_mode();
	term = init_term();
	if (ac == 1)
		while (d.exit == 0)
		{
			ft_putstr_fd("\033[0;36m\033[1mminishell ▸ \033[0m", STDERR);
			get_next_line(STDIN, &l);
			launch_minishell(&d, l);
			free(l);
		}
	else if (ac == 3 && ft_strcmp(av[1], "-c") == 0)
		launch_minishell(&d, av[2]);
	else
		ft_putstr_fd("\033[0;31mWrong arguments - Please retry\n", STDERR);
	/*print_env(d.env);
	printf("=================\n");
	print_hist(d.hist);*/
	free_all(&d);
}
