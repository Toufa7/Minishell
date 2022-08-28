/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_in_herdoc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchfa <abouchfa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 16:49:01 by otoufah           #+#    #+#             */
/*   Updated: 2022/08/27 16:04:53 by abouchfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*till_dollar(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '$')
		return (ft_strdup("$"));
	while (str[i] && str[i] != '$')
		i++;
	return (ft_substr(str, 0, i));
}

char	*exp_cases(char cases, char	*variable, char	*output)
{
	if (cases == '?')
	{
		variable = ft_itoa(g_data.errno_cp);
		return (ft_strjoin(output, variable));
	}
	return (NULL);
}

char	*get_env_in_herdoc(char *target)
{
	int		i;
	char	*output;
	char	*variable;

	i = 0;
	output = ft_strdup("");
	while (target[i])
	{
		if (target[i] == '$')
		{
			if (target[i + 1] == '?')
			{
				output = exp_cases('?', ft_itoa(g_data.errno_cp), output);
				i += 2;
			}
			else
			{
				variable = ft_substr(target + i + 1, 0,
						validate_var_name(target + i + 1));
				output = ft_strjoin(output, getenv(variable));
				i += validate_var_name(target + i + 1) + 1;
			}
		}
		else
		{
			variable = till_dollar(target + i);
			i += ft_strlen(variable);
			output = ft_strjoin(output, variable);
		}
	}
	return (output);
}
