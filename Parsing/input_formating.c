/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_formating.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchfa <abouchfa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 22:55:08 by otoufah           #+#    #+#             */
/*   Updated: 2022/08/18 15:18:40 by abouchfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	spc_allo(char *str)
{
	int	i;
	int	mem;

	i = -1;
	while (str[++i])
	{
		if ((str[i] == '<' && str[i + 1] != '<')
			|| (str[i] == '>' && str[i + 1] != '>') || str[i] == '|')
		mem++;
	}
	return (mem);
}

char	*input_formating(char *str)
{
	int		i;
	int		j;
	char	sing;
	char	*spcs;

	spcs = malloc(sizeof(char) * (ft_strlen(str) + (spc_allo(str) * 2) + 1));
	if (!spcs)
		return (NULL);
	i = -1;
	j = 0;
	while (str[++i])
	{
		if (str[i] == DOUBLES_QUOTES || str[i] == SING_QUOTES)
		{
			sing = str[i];
			spcs[j++] = str[i];
			while (str[++i] != sing && str[i])
				spcs[j++] = str[i];
		}
		if ((str[i] == '<' && str[i + 1] == '<')
			|| (str[i] == '>' && str[i + 1] == '>'))
		{
			spcs[j++] = ' ';
			spcs[j++] = str[i];
			spcs[j++] = str[i];
			spcs[j++] = ' ';
			i++;
		}
		else if ((str[i] == '>' && str[i + 1] != '>')
			|| (str[i] == '<' && str[i + 1] != '<') || str[i] == '|')
		{
			spcs[j++] = ' ';
			spcs[j++] = str[i];
			spcs[j++] = ' ';
		}
		else
			spcs[j++] = str[i];
	}
	spcs[j] = '\0';
	return (spcs);
}
