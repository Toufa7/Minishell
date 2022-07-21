/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchfa <abouchfa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 20:05:33 by otoufah           #+#    #+#             */
/*   Updated: 2022/07/21 10:22:30 by abouchfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	size_t		a;
	size_t		b;
	char		*hay;

	hay = (char *)haystack;
	if (needle[0] == 0)
		return (hay);
	a = 0;
	while (hay[a])
	{
		b = 0;
		while (hay[a + b] == needle[b])
		{
			if (needle[b + 1] == 0)
				return (&hay[a]);
			b++;
		}
		a++;
	}
	return (NULL);
}
