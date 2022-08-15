/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otoufah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 10:10:52 by otoufah           #+#    #+#             */
/*   Updated: 2022/08/15 10:10:53 by otoufah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	until_this(char *str, char until)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == until)
			break ;
	}
	return (i);
}

char	*remove_quotes(char *str, char removed)
{
	int		i;
	int		len;
	char	*new;
	char	*here;

	i = 0;
	new = "";
	while (str[i])
	{
		if (str[i] == removed)
		{
			len = until_this(&str[i + 1], removed);
			new = ft_strjoin(new, ft_substr(str + 1, i, len));
			i += len + 1;
		}
		else
		{
			here = ft_substr(&str[i], i, until_this(&str[i], removed));
			new = ft_strjoin(new, here);
			i += ft_strlen(here);
		}
	}
	return (new);
}

// int main()
// {
//     while (1)
//     {
//         char *str = readline("");
//         printf("|%s|\n", hello_quotes(str));
//     }
// }
