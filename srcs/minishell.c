/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolasessayan <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 17:24:02 by nicolases         #+#    #+#             */
/*   Updated: 2021/03/31 14:53:53 by nessayan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
		ft_exec_command(d->env, l);
}

int		main(int ac, char **av, char **env)
{
	t_data	d;
	char	*l;

	init_data(&d, env);
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
