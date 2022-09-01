/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handling_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchfa <abouchfa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 10:10:15 by otoufah           #+#    #+#             */
/*   Updated: 2022/09/01 02:06:36 by abouchfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_bool	checking_quotes(char *str)
{
	char	*check;

	check = ft_strdup(str, TRUE);
	if (s_d_quotes(check) == NULL)
	{
		ft_putstr_fd("Mini: Unclosed Quotes\n", 2);
		g_data.errno_cp = 1;
		rl_on_new_line();
		// rl_replace_line("", 0);
		return (TRUE);
	}
	return (FALSE);
}

char	*check_and_replace(char *dup, char *str, char replaced, char replace_by)
{
	size_t	i;
	char	d_or_s;

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
	return (dup);
}

char	*handling_quotes(char *str, char replaced, char replace_by)
{
	char	*dup;

	g_data.parse_error = checking_quotes(str);
	dup = NULL;
	if (!g_data.parse_error)
	{
		dup = ft_calloc((ft_strlen(str) + 1), sizeof(char), TRUE,
				"handling_quotes");
		return (check_and_replace(dup, str, replaced, replace_by));
	}
	return (dup);
}

// int main()
// {
// 	printf("%s\n",handling_quotes("omar toufah me", ' ', '*'));
// }