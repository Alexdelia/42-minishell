/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pa.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 15:52:29 by adelille          #+#    #+#             */
/*   Updated: 2021/04/09 16:53:33 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	ft_ps(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	write(1, str, i);
	return (i);
}

int	main(int ac, char **av, char **envp)
{
	int		i;

	av[80][20] = 's';
	i = 0;
	(void)ac;
	while (av[i])
	{
		ft_ps(av[i]);
		ft_ps("\n");
		i++;
	}
	i = 0;
	while (envp[i] && i < 4)
	{
		ft_ps(envp[i]);
		ft_ps("\n");
		i++;
	}
	return (42);
}