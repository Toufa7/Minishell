/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otoufah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 16:43:05 by otoufah           #+#    #+#             */
/*   Updated: 2022/08/23 16:43:10 by otoufah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**ft_realloc(char **dist, char *str)
{
	char	**tmp;
	char	**new_input;
	int		i;

	i = 0;
	tmp = dist;
	while (tmp && tmp[i])
		i++;
	new_input = ft_calloc(i + 2, sizeof(char *));
	i = -1;
	while (tmp && tmp[++i])
		new_input[i] = ft_strdup(tmp[i]);
	if (!tmp)
		i++;
	new_input[i++] = ft_strdup(str);
	new_input[i] = NULL;
	free_arr((void **) tmp);
	return (new_input);
}
