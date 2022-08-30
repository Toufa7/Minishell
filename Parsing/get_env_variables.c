/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_variables.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchfa <abouchfa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 22:32:28 by otoufah           #+#    #+#             */
/*   Updated: 2022/08/28 15:37:10 by abouchfa         ###   ########.fr       */
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


char	*gotta_expand(char *variable, char *target, t_bool flag, int *i)
{
	char *output;
	int idx;

	output = 0;
	variable = ft_substr(&target[(*i)] + 1, 0, validate_var_name(&target[(*i)] + 1));
	idx = get_var_index(add_something(variable, "="));
	if (idx != -1)
	{
		output = ft_strjoin(output, get_var_val(idx));
		(*i) += validate_var_name(&target[(*i)] + 1) + 1;
	}
	else if (flag == TRUE)
	{
		output = ft_strjoin(output, add_something("$", variable));
		(*i) += validate_var_name(&target[(*i)] + 1) + 1;
	}
	else
	{
		variable = until_dollar(&target[(*i) + 1]);
		output = ft_strjoin(output, "");
		(*i) += ft_strlen(variable) + 1;
	}
	return (output);
}

char	*get_env_variables(char *target, t_bool flag)
{
	int		i;
	char	*output;
	char	*variable;

	i = 0;
	output = ft_strdup("", TRUE);
	while ((size_t)i < ft_strlen(target))
	{
		if (target[i] == '$')
		{
			if (target[i + 1] == '?')
			{
				output = ft_strjoin(output, ft_itoa(g_data.errno_cp));
				i += 2;
			}
			else if (!ft_isalnum(target[i + 1]) && target[i + 1] != '_')
			{
				if (target[i] == '$' && (target[i + 1] == '\"' || target[i + 1] == '\''))
					i++;
				variable = until_dollar(&target[i]);
				output = ft_strjoin(output, variable);
				i += ft_strlen(variable);
			}
			else if (target[i + 1] == '\"' || target[i + 1] == '\'')
			{
				output = ft_strjoin(output, "$");
				i += 1;
			}
			else if (ft_isdigit(target[i + 1]) == 1)
			{
				if (target[i + 1] == '0')
				{
					output = ft_strjoin(output, "Minishell");
					i += ft_strlen(until_dollar(&target[i])) + 1;
				}
				else
				{
					variable = until_dollar(&target[i + 2]);
					output = ft_strjoin(output, variable);
					i += ft_strlen(variable) + 2;
				}
			}
			else
			{
				output = ft_strjoin(output, gotta_expand(variable, target, flag, &i));
			}
		}
		else
		{
			variable = until_dollar(&target[i]);
			output = ft_strjoin(output, variable);
			i += ft_strlen(variable);
		}
	}
	return (output);
}
