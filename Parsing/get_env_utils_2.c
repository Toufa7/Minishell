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
	int	flag;

	i = 0;
	flag = 0;
	if (str[i] == '$')
		return (ft_strdup("$", TRUE));
	while (str[i])
	{
		if (flag == 1 && (str[i] == '\'' || str[i] == '\"'))
			flag = str[i];
		else if (flag && str[i] == flag)
			flag = 0;
		if (str[i] == '$' && flag != '\'')
			break ;
		i++;
	}
	return (ft_substr(str, 0, i));
}

char	*just_copy(char *target, int *i)
{
	char	*output;
	char	*variable;

	output = "";
	variable = until_dollar(&target[(*i)]);
	output = ft_strjoin(output, variable);
	(*i) += ft_strlen(variable);
	return (output);
}
