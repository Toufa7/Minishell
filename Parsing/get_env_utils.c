/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otoufah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 21:15:50 by otoufah           #+#    #+#             */
/*   Updated: 2022/08/30 21:15:51 by otoufah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*gotta_expand(char *target, t_bool flag, int *i)
{
	int		idx;
	char	*output;
	char	*variable;

	output = 0;
	variable = ft_substr(&target[(*i)] + 1, 0,
			validate_var_name(&target[(*i)] + 1));
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

char	*digit(char *target, int *i)
{
	char	*output;
	char	*variable;

	output = "";
	if (target[(*i) + 1] == '0')
	{
		output = ft_strjoin(output, "Minishell");
		(*i) += ft_strlen(until_dollar(&target[(*i)])) + 1;
	}
	else
	{
		variable = until_dollar(&target[(*i) + 2]);
		output = ft_strjoin(output, variable);
		(*i) += ft_strlen(variable) + 2;
	}
	return (output);
}

char	*special_cases(char *target, int *i)
{
	char	*output;
	char	*variable;

	output = "";
	if (target[(*i)] == '$' && (target[(*i) + 1] == '\"'
			|| target[(*i) + 1] == '\''))
		(*i)++;
	variable = until_dollar(&target[(*i)]);
	output = ft_strjoin(output, variable);
	(*i) += ft_strlen(variable);
	return (output);
}

char	*exit_status(char *variable, int *i)
{
	char	*output;

	output = "";
	output = ft_strjoin(output, variable);
	(*i) += 2;
	return (output);
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
