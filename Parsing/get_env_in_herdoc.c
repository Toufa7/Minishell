/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_in_herdoc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchfa <abouchfa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 16:49:01 by otoufah           #+#    #+#             */
/*   Updated: 2022/08/28 15:40:29 by abouchfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_env_in_herdoc(char *target, t_bool flag)
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
		{
			output = ft_strjoin(output, just_copy(target, &i));
		}
	}
	return (output);
}
