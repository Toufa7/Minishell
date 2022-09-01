/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_formating.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchfa <abouchfa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 22:55:08 by otoufah           #+#    #+#             */
/*   Updated: 2022/08/28 15:16:23 by abouchfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_conditions(char current, char next)
{
	if ((current == '<' && next == '<')
		|| (current == '>' && next == '>'))
		return (1);
	else if ((current == '>' && next != '>')
		|| (current == '<' && next != '<') || current == '|')
		return (2);
	return (-1);
}

void	here_doc_or_append(char *new, char *old, int *i, int *j)
{
	new[(*j)++] = ' ';
	new[(*j)++] = old[(*i)];
	new[(*j)++] = old[(*i)];
	new[(*j)++] = ' ';
}

void	redin_or_redout_or_pipe(char *new, char *old, int *i, int *j)
{
	new[(*j)++] = ' ';
	new[(*j)++] = old[(*i)];
	new[(*j)++] = ' ';
}

void	check_inside_d_s_q(char *new, char *old, int *i, int *j)
{
	char	sing;

	if (old[(*i)] == DOUBLES_QUOTES || old[(*i)] == SING_QUOTES)
	{
		sing = old[(*i)];
		new[(*j)++] = old[(*i)];
		while (old[++(*i)] != sing && old[(*i)])
			new[(*j)++] = old[(*i)];
	}
}

char	*input_formating(char *str)
{
	int		i;
	int		j;
	char	sing;
	char	*spcs;

	spcs = alloc(sizeof(char) * (ft_strlen(str) + (spc(str) * 2) + 1), "if");
	if (!spcs)
		return (NULL);
	i = -1;
	j = 0;
	while (str[++i])
	{
		check_inside_d_s_q(spcs, str, &i, &j);
		if (check_conditions(str[i], str[i + 1]) == 1)
		{
			here_doc_or_append(spcs, str, &i, &j);
			i++;
		}
		else if (check_conditions(str[i], str[i + 1]) == 2)
			redin_or_redout_or_pipe(spcs, str, &i, &j);
		else
			spcs[j++] = str[i];
	}
	spcs[j] = '\0';
	return (spcs);
}
