/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolasessayan <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 17:24:02 by nicolases         #+#    #+#             */
/*   Updated: 2021/04/06 09:54:51 by nicolases        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		ft_min(int a, int b)
{
	if (a < b)
		return (a);
	else
		return (b);
}

int		get_size_hist(t_hist *hist)
{
	int	i;

	i = 0;
	while (hist != NULL)
	{
		i++;
		hist = hist->next;
	}
	return (i);
}

char	*get_str_hist(t_hist *hist, int index)
{
	int	i;

	i = 0;
	while (i != index)
	{
		hist = hist->next;
		i++;
	}
	return (hist->data);
}

void	pop_hist(t_data *d)
{
	t_hist *tmp;

	tmp = d->hist;
	d->hist = d->hist->next;
	free_one_hist(tmp);
}

void	put_cursor_backward(int n)
{
	int i;

	i = 0;
	while (i < n)
	{
		ft_putstr_fd("\x1b[1D", STDIN);
		i++;
	}
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

char	*append_str(char *str, char c)
{
	char	*tmp;
	int		l;
	int		i;

	if (str == NULL)
		l = 0;
	else
		l = ft_strlen(str);
	tmp = malloc(sizeof(*tmp) * (l + 2));
	i = 0;
	while (i < l)
	{
		tmp[i] = str[i];
		i++;
	}
	tmp[i] = c;
	tmp[i + 1] = '\0';
	if (str != NULL)
	{
		free(str);
		str = NULL;
	}
	return (tmp);
}

char	*pop_str(char *str)
{
	char	*tmp;
	int		l;
	int		i;

	l = ft_strlen(str);
	if (l == 1)
	{
		free(str);
		return (NULL);
	}
	tmp = malloc(sizeof(*tmp) * l);
	i = 0;
	while (i < l - 1)
	{
		tmp[i] = str[i];
		i++;
	}
	tmp[i] = '\0';
	free(str);
	str = NULL;
	return (tmp);
}

void	process_input_printable(char **l, char c)
{
	*l = append_str(*l, c);
	ft_putchar_fd(c, STDIN);
}

void	process_input_del(char **l)
{
	*l = pop_str(*l);
	put_cursor_backward(1);
}

void	process_input_newline(t_data *d, char **l)
{
	ft_putchar_fd(10, STDIN);
	if (d->ts == 1)
		pop_hist(d);
	d->hc = 0;
	d->ts = 0;
	if (*l != NULL)
	{
		store_hist(d, *l);
		ft_exec_command(*l, d->env);
	}
	ft_prompt_line();
	//ft_putstr_fd("\033[0;36m\033[1mminishell ▸ \033[0m", STDERR);
}

void	process_arrow_up(t_data *d, char **l)
{
	int		size;
	char	*tmp;

	size = get_size_hist(d->hist);
	if (size > 0)
	{
		if (d->hc == 0 && d->ts == 0)
		{
			store_hist(d, *l);
			d->ts = 1;
			size = get_size_hist(d->hist);
		}
		d->hc = ft_min(d->hc + 1, size - 1);
		if (*l != NULL)
			erase_line(l);
		tmp = get_str_hist(d->hist, d->hc);
		if (tmp == NULL)
			*l = NULL;
		else
		{
			*l = ft_strdup(tmp);
			ft_putstr_fd(*l, STDIN);
		}
	}
}

void	process_arrow_down(t_data *d, char **l)
{
	char	*tmp;

	if (d->hc > 0)
	{
		d->hc = d->hc - 1;
		if (*l != NULL)
			erase_line(l);
		tmp = get_str_hist(d->hist, d->hc);
		if (tmp == NULL)
			*l = NULL;
		else
		{
			*l = ft_strdup(tmp);
			ft_putstr_fd(*l, STDIN);
		}
	}
}

int		process_input_arrows(t_data *d, char **l)
{
	int		nread;
	char	c;

	nread = read(STDIN, &c, 1);
	if (c == 91)
	{
		nread = read(STDIN, &c, 1);
		if (c == 65)
			process_arrow_up(d, l);
		else if (c == 66)
			process_arrow_down(d, l);
	}
	return (nread);
}

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
	//ft_putstr_fd("\n\033[0;36m\033[1mminishell ▸ \033[0m", STDERR);
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

	init_data(&d, env);
	if (ac == 1)
	{
		enable_raw_mode();
		l = NULL;
		ft_prompt_line();
		//ft_putstr_fd("\033[0;36m\033[1mminishell ▸ \033[0m", STDERR);
		while (d.exit == 0)
			process_input(&d, &l);
  }
	else if (ac == 3 && ft_strcmp(av[1], "-c") == 0)
		ft_exec_command(av[2], d.env);
	else
		ft_putstr_fd("\033[0;31mWrong arguments - Please retry\n", STDERR);
	/*print_env(d.env);
	printf("=================\n");
	print_hist(d.hist);*/
	free_all(&d);
	tcsetattr(STDIN, TCSAFLUSH, &orig_termios);
}
