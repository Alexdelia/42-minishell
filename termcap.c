/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nessayan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 16:39:58 by nessayan          #+#    #+#             */
/*   Updated: 2021/04/01 14:31:16 by nessayan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <term.h>
#include "includes/minishell.h"

int	ft_putchar(int c)
{
	write(1, &c, 1);
	return (1);
}

int	init_term(void)
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

int	main(void)
{
	int term;
	char str[] = "Hello kaajlsjaljsljaljdljalsjdjsjljjsKJSLJLJLSAJADLjlsjjJljl";
	term = init_term();
	ft_putstr_fd(str, STDOUT);
	char *cap = tgetstr("le", NULL);
	int i = 0;
	while (i < (int)ft_strlen(str) - 10)
	{
		tputs (cap, STDOUT, ft_putchar);
		i++;
	}
	/*printf("co = %d; li = %d\n", tgetnum("c"), tgetnum("li"));
	printf("os = %d\n", tgetflag("os"));
	char *cl_cap = tgetstr("md", NULL);
	tputs (cl_cap, STDOUT, ft_putchar);
	printf("Coucou\n");
	char* color_cap = tgetstr("AF", NULL);
	tputs(tparm(color_cap, COLOR_GREEN), 1, ft_putchar);
	printf("Du vert!\n");
	char *me_cap = tgetstr("me", NULL);
	tputs (me_cap, STDOUT, ft_putchar);
	printf("Retour a la normal\n");
	tputs(tparm(color_cap, COLOR_GREEN), 1, putchar);
	char *underline_cmd = tgetstr("us", NULL);
	tputs(underline_cmd, 1, putchar);
	tputs(cl_cap, 1, putchar);
	printf("Texte vert souligné\n");
	char *cm_cap = tgetstr("cm", NULL);
	tputs(tgoto(cm_cap, 5, 5), 1, putchar);*/
}
