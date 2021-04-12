/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_word_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 06:51:14 by adelille          #+#    #+#             */
/*   Updated: 2021/04/12 13:44:59 by nicolases        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	get_start_index(char *line, int process_num)
{
	int	i;

	i = 0;
	while (line[i] != '\0' && process_num > 0)
	{
		if (line[i] == '|' || line[i] == ';')
			process_num--;
		else if (line[i] == '>')
		{
			process_num--;
			if (line[i + 1] != '\0' && line[i + 1] == '>')
				i++;
		}
		else if (line[i] == '<')
		{
			process_num--;
			if (line[i + 1] != '\0' && line[i + 1] == '<')
				i++;
		}
		i++;
	}
	return (i);
}

int	get_end_index(char *line, int start)
{
	int	j;

	j = start;
	while (line[j] != '\0' && line[j] == ' ')
		j++;
	while (line[j] != '\0' && line[j] != ';' && line[j] != '|'
		&& line[j] != '<' && line[j] != '>' && line[j] != ' ')
		j++;
	while (line[j] != '\0' && line[j] == ' ')
		j++;
	return (j);
}

/*static t_word	*ft_error_ml(t_word **word)
{
	ft_pserc("Error: multiligne\n", RED);
	ft_free_all_word(*word);
	return (NULL);
}*/

void	ft_word_split(t_data *d, char *line, int process_num)
{
	int		i;
	int		j;
	char		*s1;
	char		*s2;
	(void)d;
	i = get_start_index(line, process_num);
	j = get_end_index(line, i);
	s1 = ft_strdup2(line, i, j);
	s2 = ft_strtrim(s1, " ");
	free(s1);
	d->word = ft_new_word(s2);
	//ft_add_back_word(&(d->word), ft_new_word(str));
	free(s2);
	// j = get_end_index(line, process_num);
	// parse_convert_cmd(t_wor**word, t_data *d, 
	/*i = ft_cmd(&word, d, str, i);
	if (i < 0)
		return (ft_error_ml(&word));
	i = ft_content(&word, d, str, i + 1);
	if (i < 0)
		return (ft_error_ml(&word));*/
}
