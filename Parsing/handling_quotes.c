/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handling_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchfa <abouchfa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 10:10:15 by otoufah           #+#    #+#             */
/*   Updated: 2022/08/21 06:57:12 by abouchfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	checking_quotes(char *str)
{
	if (ft_strcmp(singles_doubles_quotes(str), "Error") == 0)
	{
		ft_putstr_fd("Unclosed Quotes\n", 2);
		global_data.errno_cp = 1;
		rl_on_new_line();
		rl_replace_line("", 0);
		return (TRUE);
	}
	return (FALSE);
}

// This function aims to if it found something that we split with like space of | we well repalace it with something else


char	*handling_quotes(char *str, char replaced, char replace_by)
{
	int		i;
	int		j;
	char	*dup;

	// printf("Entering -> %s\n",str);
	// global_data.parse_error = checking_quotes(str);
	// dup = NULL;
	// if (!global_data.parse_error)
	// {
		dup = malloc(sizeof(char) * (ft_strlen(str) + 1));
		if (!dup)
			return (NULL);
		i = 0;
		while (str[i] && i < strlen(str) - 1)
		{
			// "'"
			if (str[i] == DOUBLES_QUOTES || str[i] == SING_QUOTES)
			{
				j = i;
				if (str[j] == DOUBLES_QUOTES || str[j] == SING_QUOTES)
				{
					dup[j] = str[j];
					j++;
				}
				while (str[j] && str[j] != DOUBLES_QUOTES && str[j] != SING_QUOTES)
				{
					if (str[j] == replaced)
						dup[j] = replace_by;
					else
						dup[j] = str[j];
					j++;
				}
				if (str[j] && (str[j] == DOUBLES_QUOTES || str[j] == SING_QUOTES))
				{
					dup[j] = str[j];
					printf("Dup %c Str %c\n",dup[j],str[j]);
				}
				i = j;
			}
			else
			{
				dup[i] = str[i];
			}
			i++;
		}
		dup[i] = '\0';
		// free_str(str);
		return (dup);
	}
// }
