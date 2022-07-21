/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchfa <abouchfa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 00:56:50 by otoufah           #+#    #+#             */
/*   Updated: 2022/07/21 10:22:30 by abouchfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	*ft_calloc(size_t count, size_t size)
{
	char	*booked;
	size_t	memory;
	size_t	i;

	i = 0;
	memory = count * size;
	booked = (void *)malloc(memory);
	if (booked == NULL)
		return (NULL);
	while (i < memory)
	{
		booked[i] = 0;
		i++;
	}
	return (booked);
}
