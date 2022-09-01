/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mexport_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchfa <abouchfa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 05:14:07 by abouchfa          #+#    #+#             */
/*   Updated: 2022/09/01 21:52:57 by abouchfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_key(char *str)
{
	char	*key;
	int		i;

	i = 0;
	key = NULL;
	while (str[i] && str[i] != '=' && str[i] != '+')
	{
		if (!(ft_isalpha(str[i]) || str[i] == BACKSLASH
				|| (ft_isdigit(str[i]) && i != 0) || str[i] == '_'))
			break ;
		i++;
	}
	printf("str: %s")
	if (i > 0 && (!str[i] || str[i] == '=' || str[i] == '+'))
	{
		key = alloc(sizeof(char) * (i + 1), "export val");
		ft_strncpy(key, str, i);
	}
	return (key);
}

char	*get_val(char *str)
{
	char	*val;
	int		i;
	int		j;

	i = 0;
	j = 0;
	val = NULL;
	while (str[i] && str[i] != '=')
		i++;
	if (str[i])
	{
		while (str[i + j])
			j++;
		val = alloc(sizeof(char) * (j + 1), "export val");
		ft_strncpy(val, str + i + 1, j);
	}
	return (val);
}

/*
	-1: invalid op
	 0: Create var
	 1: Add to var
	 2: Just a var name
*/

int	get_op_type(char *str)
{
	int	type;

	type = -1;
	if (!str || !str[0])
		type = 2;
	if (str[0] && str[0] == '=')
		type = 0;
	if (str[0] && str[1] && str[0] == '+' && str[1] == '=')
		type = 1;
	return (type);
}
