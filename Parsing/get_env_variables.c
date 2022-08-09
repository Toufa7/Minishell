/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_variables.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchfa <abouchfa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 22:32:28 by otoufah           #+#    #+#             */
/*   Updated: 2022/08/02 12:46:03 by abouchfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	untill_this(char *var)
{
	int	i;

	i = 0;
	while (var[i] && ft_isalpha(var[i]))
		i++;
	return (i);
}

char	*until_dollar(char *str, int start)
{
	int i = start;

	while (str[i] && str[i] != '$')
		i++;
	return (ft_substr(str, start, i));
}

char	*get_env_variables(char *target)
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
			variable = ft_substr(target + i + 1, 0, untill_this(target + i + 1));
			output = ft_strjoin(output, getenv(variable));
			i += untill_this(target + i + 1) + 1;
		}
		else
		{
			variable = until_dollar(target, i);
			i += ft_strlen(variable);
			// pritnf("%d\n", ft_strlen(variable));
			output = ft_strjoin(output, variable);
			
		}
	}
	free_str(target);
	return output;
}


// int main(int a, char **b, char **env)
// {
// 	env_dup(env);
// 	while (1)
// 	{
// 		char *s = readline("");
// 		printf("%s\n", get_env_variables(s));
// 	}
// }