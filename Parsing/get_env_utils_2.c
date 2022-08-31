/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otoufah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 21:32:22 by otoufah           #+#    #+#             */
/*   Updated: 2022/08/30 21:32:23 by otoufah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*add_something(char *str, char *add)
{
	return (ft_strjoin(str, add));
}

char	*until_dollar(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '$')
		return (ft_strdup("$", TRUE));
	while (str[i] && str[i] != '$')
	{
		i++;
	}
	return (ft_substr(str, 0, i));
}
