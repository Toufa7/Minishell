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

int	spc(char *str)
{
	int	i;
	int	mem;

	i = -1;
	mem = 0;
	while (str[++i])
	{
		if ((str[i] == '<' && str[i + 1] != '<')
			|| (str[i] == '>' && str[i + 1] != '>') || str[i] == '|')
		mem++;
	}
	return (mem);
}

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

char	*input_formating(char *str)
{
	int		i;
	int		j;
	char	sing;
	char	*spcs;

	spcs = alloc(sizeof(char) * (ft_strlen(str) + (spc(str) * 2) + 1), "frmt");
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
		if (check_conditions(str[i], str[i + 1]) == 1)
		{
			spcs[j++] = ' ';
			spcs[j++] = str[i];
			spcs[j++] = str[i];
			spcs[j++] = ' ';
			i++;
		}
		else if (check_conditions(str[i], str[i + 1]) == 2)
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

// int main()
// {
// 	char *s = "omar>toufah>>me";
// 	printf("%s\n",input_formating(s));
// }
