/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 10:39:17 by adelille          #+#    #+#             */
/*   Updated: 2021/04/13 12:50:38 by nicolases        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		ft_putchar(int c)
{
	write(1, &c, 1);
	return (1);
}

int		init_term(void)
{
	int			ret;
	char		*term_type;

	term_type = getenv("TERM");
	if (term_type == NULL)
		return (ft_mi_error("termcap", "TERM must be set (see 'env')", -1));
	ret = tgetent(NULL, term_type);
	if (ret == -1)
		return (ft_mi_error("termcap", "Could not access database", -1));
	else if (ret == 0)
		return (ft_mi_error("termcap", "terminal type is not defined", -1));
	return (0);
}

int		ft_prompt_line(void)
{
	char	path[PATH_LEN];
	int		i;
	int		y;

	getcwd(path, PATH_LEN - 1);
	i = 0;
	y = 0;
	while (path[i])
	{
		if (path[i] == '/')
			y = i;
		i++;
	}
	ft_pserc("➜  ", GRN);
	ft_pserc("minishell ", "\033[1;36m");
	ft_pserc(&path[y + 1], BIMAG);
	ft_pserc(" ▸ ", "\033[1;36m");
	return (0);
}

void	put_cursor_backward(int n)
{
	int		i;
	char	*tc1;
	char	*tc2;

	if (TERMCAP)
	{
		tc1 = tgetstr("le", NULL);
		tc2 = tgetstr("ce", NULL);
	}
	i = 0;
	while (i < n)
	{
		if (TERMCAP)
			tputs(tc1, STDIN, ft_putchar);
		else
			ft_putstr_fd("\x1b[1D", STDIN);
		i++;
	}
	if (TERMCAP)
		tputs(tc2, STDIN, ft_putchar);
	else
		ft_putstr_fd("\x1b[K", STDIN);
}

void	erase_line(char **l)
{
	int size;

	size = ft_strlen(*l);
	put_cursor_backward(size);
	free(*l);
	*l = NULL;
}
