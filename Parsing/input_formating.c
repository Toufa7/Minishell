/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_formating.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otoufah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 22:55:08 by otoufah           #+#    #+#             */
/*   Updated: 2022/07/02 22:55:09 by otoufah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*input_formating(char *str)
{
	int		i;
	int		j;
	int		k;
	int		allo;
	char	*spcs;

	k = -1;
	allo = 0;
	while (str[++k])
	{
		if ((str[k] == '<' && str[k + 1] != '<') || (str[k] == '>'
				&& str[k + 1] != '>') || str[k] == '|' || str[k] == '$')
			allo++;
	}
	spcs = malloc(sizeof(char) * (ft_strlen(str) + (allo * 2) + 1));
	if (!spcs)
		return (NULL);
	i = -1;
	j = 0;
	while (str[++i])
	{
		if ((str[i] == '<' && str[i + 1] == '<')
			|| (str[i] == '>' && str[i + 1] == '>'))
		{
			spcs[j++] = ' ';
			spcs[j++] = str[i];
			spcs[j++] = str[i];
			i++;
		}
		else if ((str[i] == '>' && str[i + 1] != '>') || (str[i] == '<'
				&& str[i + 1] != '<') || str[i] == '|' || str[i] == '$')
		{
			spcs[j++] = ' ';
			spcs[j++] = str[i];
			spcs[j++] = ' ';
		}
		else
			spcs[j++] = str[i];
	}
	spcs[j] = '\0';
	free(str);
	return (spcs);
}
