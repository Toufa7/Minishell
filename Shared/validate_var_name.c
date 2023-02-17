/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_var_name.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otoufah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 16:43:29 by otoufah           #+#    #+#             */
/*   Updated: 2022/08/23 16:43:30 by otoufah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
	This function return the index where it find invalid char in var name
	You can check if the var name is valid using:
	if (var[i] == '\0') --> the var name is valid
	else --> not a valid name
*/

int	validate_var_name(char *var)
{
	int	i;

	i = -1;
	while (var[++i])
	{
		if (!(ft_isalpha(var[i])
				|| (ft_isdigit(var[i]) && i != 0) || var[i] == '_'))
			break ;
	}
	return (i);
}
