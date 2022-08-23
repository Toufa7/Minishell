/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_variables.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchfa <abouchfa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 22:32:28 by otoufah           #+#    #+#             */
/*   Updated: 2022/08/22 14:44:47 by abouchfa         ###   ########.fr       */
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
		return (ft_strdup("$"));
	while (str[i] && str[i] != '$')
	{
		i++;
	}
	return (ft_substr(str, 0, i));
}

char	*get_env_variables(char *target, bool flag)
{
	int		i;
	int		idx;
	char	*output;
	char	*env_var;
	char	*variable;

	i = 0;
	output = ft_strdup("");
	while (i < ft_strlen(target))
	{
		if (target[i] == '$')
		{
			if (target[i + 1] == '?')
			{
				variable = ft_itoa(global_data.errno_cp);
				output = ft_strjoin(output, variable);
				i += 2;
			}
			else if (ft_isdigit(target[i + 1]) == 1)
			{
				if (target[i + 1] == '0')
				{
					variable = ft_strdup("Minishell");
					output = ft_strjoin(output, variable);
					i += ft_strlen(variable);
				}
				else
				{
					variable = &target[i + 2];
					output = ft_strjoin(output, variable);
					i += ft_strlen(variable);
				}
			}
			else
			{
				variable = ft_substr(target + i + 1, 0, validate_var_name(target + i + 1));           	// echo "$\USER" == $\USER	[❓]
				env_var = add_something(variable, "=");													// echo "\USER"  == \USER	[✅]
				idx = get_var_index(add_something(variable, "="));										// echo "\$USER" == $USER	[❓]
				if (idx != -1)
				{
					output = ft_strjoin(output, get_var_val(idx, FALSE));
					i += validate_var_name(target + i + 1) + 1;
				}
				else if (flag == TRUE)
				{
					output = ft_strjoin(output, add_something("$", variable));
					i += validate_var_name(target + i + 1) + 1;
				}
				else
				{
					output = ft_strjoin(output, "");
					i += validate_var_name(target + i + 1) + 1;	
				}
			}
		}
		else
		{
			variable = until_dollar(target + i);
			output = ft_strjoin(output, variable);
			i += ft_strlen(variable);
		}
		// free_str(variable);
	}
	// free_str(target);
	return output;
}