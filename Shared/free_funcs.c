/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_funcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchfa <abouchfa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 16:40:32 by otoufah           #+#    #+#             */
/*   Updated: 2022/09/01 04:27:27 by abouchfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_str(void *ptr)
{
	if (ptr)
		free(ptr);
}

void	free_arr(void **arr)
{
	int	i;

	i = -1;
	while (arr && arr[++i])
		free_str(arr[i]);
	free(arr);
}
