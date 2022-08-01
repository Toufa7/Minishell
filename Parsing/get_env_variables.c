/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_variables.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchfa <abouchfa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 22:32:28 by otoufah           #+#    #+#             */
/*   Updated: 2022/08/01 15:42:36 by abouchfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	untill_this(char *var)
{
	int	i;

	i = -1;
	while (var[++i])
	{
		while (var[i] == '$')
			i++;
		if (!(ft_isalpha(var[i]) || (ft_isdigit(var[i]) && i != 0)
				|| var[i] == '_'))
			break ;
	}
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
	int		j;
	char	*test = "";
	char	*tmp;

	j = 0;
	while (target[j])
	{
		if (target[j] == '$')
		{
			tmp = ft_substr(target , j + 1, untill_this(target) - 1);
			test = ft_strjoin(test, getenv(tmp));
			printf("Test -> %s\n",test);
			j += untill_this(target + j) - 1;
			printf("j through ->%d\n",j);
		}
		else
		{
			tmp = until_dollar(target, j);
			printf("%s\n", tmp);

			j += ft_strlen(tmp);
			printf("j -> %d\n",j);
			test = ft_strjoin(test, tmp);
		}
	}
	// free_str(target);
	return test;
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

// e