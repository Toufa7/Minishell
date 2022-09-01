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

int	should_not_be_expanded(char	**str)
{
	int	i;
	int	j;

	i = 0;

	while (str[i])
	{
		j = 0;
		while (str[i][j])
		{
			if (str[i][j] == SING_QUOTES || str[i][j] == DOUBLES_QUOTES)
			{
				return (1);
			}
			j++;
		}
		i++;
	}
	return (-1);
}

// void	loop_and_check(t_pipe_data *pipe_data)
// {
// 	int i = 0;
// 	while (i < pipe_data->counter.delimiter)
// 	{
// 		printf("Rslt => %d\n", should_not_be_expanded(&pipe_data->delimiter[i]));
// 		i++;
// 	}
// }

char	*get_env_in_herdoc(char *target, t_bool flag, t_pipe_data *pipe_data)
{
	int		i = 0;
	char	*output;
	int		yes_or_no;

	output = ft_strdup("", TRUE);
	yes_or_no = should_not_be_expanded(&pipe_data->delimiter[0]);
	while ((size_t)i < ft_strlen(target))
	{
		if (target[i] == '$' && yes_or_no != 1)
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
