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

/*
	This Function aim to creat spaces 
*/

char	*input_formating(char *str)
{
	int		i;
	int		j;
	int		allo;
	char	sing;
	char	*spcs;

	i = -1;
	allo = 0;
	while (str[++i])
	{
		if ((str[i] == '<' && str[i + 1] != '<')
			|| (str[i] == '>' && str[i + 1] != '>') || str[i] == '|')
			allo++;
	}
	spcs = malloc(sizeof(char) * (ft_strlen(str) + (allo * 2) + 1));
	if (!spcs)
		return (NULL);
	i = -1;
	j = 0;
	while (str[++i])
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			sing = str[i];
			spcs[j++] = str[i];
			while (str[++i] != sing && str[i])
			{
				spcs[j++] = str[i];
			}
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
	free(str);
	return (spcs);
}

// int main()
// {
// 	while (TRUE)
// 	{
// 	char *s = readline(""); printf("%s\n",input_formating(s));
// 	}
// }
