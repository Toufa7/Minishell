/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handling_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otoufah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 10:10:15 by otoufah           #+#    #+#             */
/*   Updated: 2022/08/15 10:10:17 by otoufah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	checking_quotes(char *str)
{
	if (counting_quotes(str, 'D') % 2 != 0)
	{
		ft_putstr_fd("Unclosed Doubles Quotes\n", 2);
		rl_on_new_line();
		rl_replace_line("", 0);
		return (TRUE);
	}
	else if (counting_quotes(str, 'S') % 2 != 0)
	{
		ft_putstr_fd("Unclosed Singles Quotes\n", 2);
		rl_on_new_line();
		rl_replace_line("", 0);
		return (TRUE);
	}
	return (FALSE);
}

char	*handling_quotes(char *str, char replaced_1, char replaced_2, char replace_by)
{
	int		i;
	int		j;
	char	*dup;

	global_data.parse_error = checking_quotes(str);
	dup = NULL;
	if (!global_data.parse_error)
	{
		dup = malloc(sizeof(char) * (ft_strlen(str) + 1));
		if (!dup)
			return (NULL);
		i = -1;
		while (str[++i])
		{
			if (str[i] == DOUBLES_QUOTES || str[i] == SING_QUOTES)
			{
				j = i;
				if (str[j] == DOUBLES_QUOTES || str[j] == SING_QUOTES)
					dup[j] = str[j];
				j = j + 1;
				while (str[j] != DOUBLES_QUOTES && str[j] != SING_QUOTES)
				{
					if (str[j] == replaced_1 || str[j] == replaced_2)
						dup[j] = replace_by;
					else
						dup[j] = str[j];
					j++;
				}
				if (str[j] == DOUBLES_QUOTES || str[j] == SING_QUOTES)
					dup[j] = str[j];
				i = j;
			}
			else
				dup[i] = str[i];
		}
		dup[i] = '\0';
		free_str(str);
	}
	return (dup);
}
