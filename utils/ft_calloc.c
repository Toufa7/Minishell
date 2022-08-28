/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchfa <abouchfa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 00:56:50 by otoufah           #+#    #+#             */
/*   Updated: 2022/08/28 15:56:42 by abouchfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	*ft_calloc(size_t count, size_t size, t_bool use_alloc, char *source)
{
	char	*booked;
	size_t	memory;
	size_t	i;

	i = 0;
	memory = count * size;
	printf("Count => %zu Size => %zu Spirce => %s\n", count, size, source);
	if (use_alloc)
		booked = alloc(memory, "ft_calloc");
	else
		booked = malloc(memory);
	if (booked == NULL)
		return (NULL);
	while (i < memory)
	{
		booked[i] = 0;
		i++;
	}
	return (booked);
}
