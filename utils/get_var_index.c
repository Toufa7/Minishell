/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_var_index.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otoufah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 16:41:39 by otoufah           #+#    #+#             */
/*   Updated: 2022/08/23 16:41:40 by otoufah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
	this function return the index of a key from global_data.envp
		(our global environment variables)
	return -1 if the key don't exist
*/

int	get_var_index(char *key)
{
	int	j;
	int	i;

	j = -1;
	i = -1;
	while (global_data.envp[++j])
	{
		if (ft_strncmp(global_data.envp[j], key, ft_strlen(key)) == 0)
		{
			i = j;
			break ;
		}
	}
	return (i);
}
