/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchfa <abouchfa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 20:05:07 by otoufah           #+#    #+#             */
/*   Updated: 2022/08/28 15:22:08 by abouchfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strdup(const char *s1, t_bool use_alloc)
{
	char	*dup;
	size_t	i;
	size_t	l;
	size_t	memory;

	l = ft_strlen(s1);
	memory = (sizeof(char) * l + 1);
	if (use_alloc)
		dup = alloc(memory, "ft_strdup");
	else
		dup = malloc(memory);
	if (!(dup && s1))
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		dup[i] = s1[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}
