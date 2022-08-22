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
	char *check = ft_strdup(str);
	if (singles_doubles_quotes(check) == NULL)
	{
		ft_putstr_fd("Unclosed Quotes\n", 2);
		global_data.errno_cp = 1;
		rl_on_new_line();
		rl_replace_line("", 0);
		return (TRUE);
	}
	return (FALSE);
}

char	*handling_quotes(char *str, char replaced, char replace_by)
{
	int		i;
	int		j;
	char	*dup;

	global_data.parse_error = checking_quotes(str);
	dup = NULL;
	if (!global_data.parse_error)
	{
		dup = ft_calloc((ft_strlen(str) + 1), sizeof(char));
		if (!dup)
			return (NULL);
		i = -1;
		while (++i < ft_strlen(str))
		{
			if (str[i] == DOUBLES_QUOTES || str[i] == SING_QUOTES)
			{
				j = i;
				if (str[j] == DOUBLES_QUOTES || str[j] == SING_QUOTES)
				{
					dup[j] = str[j];
					j = j + 1;
				}
				while (str[j] && str[j] != DOUBLES_QUOTES && str[j] != SING_QUOTES)
				{
					if (str[j] == replaced)
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
		// free_str(str);
	}
	return (dup);
}
