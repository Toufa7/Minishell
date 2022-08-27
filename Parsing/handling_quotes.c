/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handling_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchfa <abouchfa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 10:10:15 by otoufah           #+#    #+#             */
/*   Updated: 2022/08/26 18:31:53 by otoufah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	checking_quotes(char *str)
{
	char	*check;

	check = ft_strdup(str);
	if (s_d_quotes(check) == NULL)
	{
		ft_putstr_fd("Unclosed Quotes\n", 2);
		global_data.errno_cp = 1;
		// rl_on_new_line();
		// rl_replace_line("", 0);
		return (TRUE);
	}
	return (FALSE);
}

char	*handling_quotes(char *str, char replaced, char replace_by)
{
	int		i;
	char	*dup;
	char	d_or_s;

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
				dup[i] = str[i];
				d_or_s = dup[i];
				while (str[++i] && str[i] != d_or_s)
				{
					if (str[i] == replaced)
						dup[i] = replace_by;
					else
						dup[i] = str[i];
				}
				if (str[i] == DOUBLES_QUOTES || str[i] == SING_QUOTES)
					dup[i] = str[i];
			}
			else
				dup[i] = str[i];
		}
	}
	return (dup);
}

// int main()
// {
// 	while (TRUE)
// 	{
// 		char *s = readline("");printf("%s\n",handling_quotes(s, ' ', -1));
// 	}
// }