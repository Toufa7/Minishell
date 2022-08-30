/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_d_quotes.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otoufah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 17:00:50 by otoufah           #+#    #+#             */
/*   Updated: 2022/08/26 16:25:03 by otoufah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	until_this(char *str, char c)
{
	int	i;

	if (!str)
		return (0);
	i = -1;
	while (str[++i])
	{
		if (str[i] == c)
			break ;
	}
	return (i);
}

char	*replace_them(char *str, char replaced)
{
	int	i;
	int	j;

	if (!str)
		return (NULL);
	i = -1;
	j = 0;
	while (str[++i])
	{
		if (str[i] == replaced)
			continue ;
		str[j] = str[i];
		j++;
	}
	str[j] = '\0';
	return (str);
}

char	*s_d_quotes(char *str)
{
	int		i;
	int		len;
	char	selected;
	char	replaced;

	if (!str)
		return (NULL);
	i = -1;
	while (str[++i])
	{
		if (str[i] == SING_QUOTES || str[i] == DOUBLES_QUOTES)
		{
			selected = str[i];
			replaced = -1;
			len = until_this(&str[i + 1], selected);
			if (str[len + i + 1] == '\0')
				return (NULL);
			str[i] = replaced;
			str[len + i + 1] = replaced;
			i += len;
		}
	}
	return (replace_them(str, replaced));
}
