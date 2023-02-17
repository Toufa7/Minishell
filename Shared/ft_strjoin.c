/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchfa <abouchfa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 20:05:16 by otoufah           #+#    #+#             */
/*   Updated: 2022/08/28 15:18:40 by abouchfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*join;
	int		i;
	int		j;

	if (s1 == 0 && s2 == 0)
		return (NULL);
	join = alloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1),
			"ft_strjoin");
	if (!join)
		return (NULL);
	i = 0;
	j = 0;
	while (s1 && s1[i] != '\0')
	{
		join[j++] = s1[i++];
	}
	i = 0;
	while (s2 && s2[i] != '\0')
	{
		join[j++] = s2[i++];
	}
	join[j] = '\0';
	return (join);
}
