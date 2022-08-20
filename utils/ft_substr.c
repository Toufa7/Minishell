/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchfa <abouchfa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 20:05:38 by otoufah           #+#    #+#             */
/*   Updated: 2022/07/21 10:22:30 by abouchfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	i;
	size_t	l;
	size_t	memory;

	if (!s)
		return (NULL);
	memory = (sizeof(char) * len + 1);
	sub = (char *)malloc(memory);
	if (!sub)
		return (NULL);
	i = 0;
	l = 0;
	while (s[i] != '\0')
	{
		if (i >= start && l < len)
		{
			sub[l] = s[i];
			l++;
		}
		i++;
	}
	sub[l] = '\0';
	return (sub);
}