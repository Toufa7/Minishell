/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otoufah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 16:42:45 by otoufah           #+#    #+#             */
/*   Updated: 2022/08/23 16:42:46 by otoufah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strchr(const char *s, int c)
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
			return (&string[i + 1]);
		i++;
	}
	if (alpha == 0)
		return (&string[i]);
	return (0);
}
