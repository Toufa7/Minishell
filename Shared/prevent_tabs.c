/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prevent_tabs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otoufah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 01:09:18 by otoufah           #+#    #+#             */
/*   Updated: 2022/09/03 01:09:19 by otoufah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strchrr(const char *s, int c)
{
	int				i;
	unsigned char	alpha;
	char			*string;

	if (!s || !c)
		return (NULL);
	string = (char *)s;
	alpha = c;
	i = 0;
	while (string[i] != '\0')
	{
		if (string[i] == alpha)
			return (&string[i]);
		i++;
	}
	if (alpha == 0)
		return (&string[i]);
	return (0);
}

char	ft_until(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != TAAB)
			return (str[i]);
		i++;
	}
	return (-1);
}

char	*prevent_tabs(char *str)
{
	char	until;

	until = ft_until(str);
	return (ft_strchrr(str, until));
}
