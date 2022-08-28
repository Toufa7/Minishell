/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchfa <abouchfa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 16:43:05 by otoufah           #+#    #+#             */
/*   Updated: 2022/08/28 15:54:45 by abouchfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**ft_realloc(char **dist, char *str, t_bool use_alloc)
{
	char	**tmp;
	char	**new_input;
	int		i;

	i = 0;
	tmp = dist;
	while (tmp && tmp[i])
		i++;
	new_input = ft_calloc(i + 2, sizeof(char *), use_alloc);
	i = -1;
	while (tmp && tmp[++i])
		new_input[i] = ft_strdup(tmp[i], use_alloc);
	if (!tmp)
		i++;
	new_input[i++] = ft_strdup(str, use_alloc);
	new_input[i] = NULL;
	return (new_input);
}
