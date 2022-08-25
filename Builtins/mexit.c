/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mexit.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchfa <abouchfa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 16:19:54 by otoufah           #+#    #+#             */
/*   Updated: 2022/08/25 04:10:50 by abouchfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	mexit(char **argv)
{
	bool	is_valid;
	bool	is_digit;
	int		j;
	int		i;

	is_valid = TRUE;
	i = 0;
	j = 0;
	if (!ft_strcmp(argv[i], "--"))
		i++;
	if (argv[i] && (argv[i][j] == '-' || argv[i][j] == '+'))
		j++;
	if (argv[i] && !argv[i][j])
		is_valid = FALSE;
	while (argv[i] && argv[i][j])
	{
		if (!(argv[i][j] >= '0' && argv[i][j] <= '9'))
		{
			is_valid = FALSE;
			break ;
		}
		j++;
	}
	while (argv[i])
		i++;
	if (!is_valid)
	{
		ft_putstr_fd("exit\nexit: ", 2);
		ft_putstr_fd(argv[0], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		global_data.errno_cp = 255;
		exit(255);
	}
	else if (i > 1)
	{
		ft_putstr_fd("exit\nexit: too many arguments\n", 2);
		global_data.errno_cp = 1;
		return ;
	}
	else
	{
		if (argv[i])
			global_data.errno_cp = ft_atoi(argv[i]) % 256;
		printf("exit\n");
		exit(global_data.errno_cp);
	}
}
