/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_var_val.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchfa <abouchfa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 16:41:44 by otoufah           #+#    #+#             */
/*   Updated: 2022/08/27 14:27:16 by abouchfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_var_val(int var_index)
{
	char	*val;
	char	*var;
	int		i;
	int		j;

	i = 0;
	j = 0;
	val = NULL;
	var = global_data.envp[var_index];
	while (var[i] && var[i] != '=')
		i++;
	if (var[i])
	{
		while (var[i + j])
			j++;
		val = alloc(sizeof(char) * (j + 1));
		ft_strncpy(val, var + i + 1, j);
	}
	return (val);
}
