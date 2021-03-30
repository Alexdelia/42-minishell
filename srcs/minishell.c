/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolasessayan <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 17:24:02 by nicolases         #+#    #+#             */
/*   Updated: 2021/03/30 18:34:14 by nicolases        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_all(t_data *d)
{
	free_all_env(d->env);
}

void	init_data(t_data *d, char **env)
{
	d->cmd = NULL;
	d->env = init_env(env);
	d->exit = 0;
}

int		main(int ac, char **av, char **env)
{
	t_data	d;
	char	*l;

	(void)ac;
	(void)av;
	init_data(&d, env);
	while (d.exit == 0)
	{
		ft_putstr_fd("\033[0;36m\033[1mminishell ▸ \033[0m", STDERR);
		get_next_line(STDIN, &l);
		if (l[0] == '\0')
			d.exit = 1;
		free(l);
	}
	print_env(d.env);
	free_all(&d);
}
