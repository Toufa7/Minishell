/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_variables.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchfa <abouchfa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 22:32:28 by otoufah           #+#    #+#             */
/*   Updated: 2022/09/01 03:23:02 by abouchfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_env_variables(char *target, t_bool flag)
{
	int		i;
	char	*output;

	i = 0;
	output = ft_strdup("", TRUE);
	while ((size_t)i < ft_strlen(target))
	{
		if (target[i] == '$')
		{
			if (target[i + 1] == '?')
				output = ft_strjoin(output,
						exit_status(ft_itoa(g_data.errno_cp), &i));
			else if (!ft_isalnum(target[i + 1]) && target[i + 1] != '_')
				output = ft_strjoin(output, special_cases(target, &i));
			else if (ft_isdigit(target[i + 1]) == 1)
				output = ft_strjoin(output, digit(target, &i));
			else
				output = ft_strjoin(output, gotta_expand(target, flag, &i));
		}
		else
			output = ft_strjoin(output, just_copy(target, &i));
	}
	return (output);
}

/*
	else if ((target[i + 1] == '\"' && target[i + 2] != '\"')
		|| (target[i + 1] == '\'' && target[i + 2] != '\''))
	{
		output = ft_strjoin(output, "$");
		i+=1;
	}
*/
