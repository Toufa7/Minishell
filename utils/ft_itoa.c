/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchfa <abouchfa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 16:43:39 by otoufah           #+#    #+#             */
/*   Updated: 2022/08/27 14:27:16 by abouchfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	nbrtoi(char	*str, int size, long int nb)
{
	if (nb == 0)
		str[0] = '0';
	str[--size] = 0;
	if (nb < 0)
	{
		str[0] = '-';
		nb = -nb;
	}
	while (nb > 0)
	{
		str[--size] = (nb % 10) + 48;
		nb /= 10;
	}
}

char	*ft_itoa(int n)
{
	long int	temp_n;
	int			size;
	char		*str;

	size = 1;
	temp_n = n;
	if (temp_n <= 0)
	{
		temp_n = -temp_n;
		size++;
	}
	while (temp_n > 0)
	{
		temp_n /= 10;
		size++;
	}
	str = alloc(size * sizeof(char));
	if (!str)
		return (NULL);
	nbrtoi(str, size, (long int) n);
	return (str);
}
