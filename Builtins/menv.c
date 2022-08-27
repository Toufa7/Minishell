/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menv.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchfa <abouchfa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 16:19:50 by otoufah           #+#    #+#             */
/*   Updated: 2022/08/23 16:19:51 by otoufah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	menv(char **argv, char *prefix, t_bool is_export)
{
	int	eq;
	int	i;
	int	j;

	i = -1;
	if (argv && *argv)
	{
		ft_putstr_fd("env: ", 2);
		ft_putstr_fd(*argv, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		g_global_data.errno_cp = 127;
	}
	else
	{
		while (g_global_data.envp[++i])
		{
			j = -1;
			while (g_global_data.envp[i][++j])
				if (g_global_data.envp[i][j] == '=')
					break ;
			if (g_global_data.envp[i][j] != '=' && !is_export)
				continue ;
			j = -1;
			eq = 0;
			ft_putstr_fd(prefix, g_global_data.out_fd);
			while (g_global_data.envp[i][++j])
			{
				write(1, g_global_data.envp[i] + j, g_global_data.out_fd);
				if (g_global_data.envp[i][j] == '=' && is_export)
				{
					write(1, "\"", g_global_data.out_fd);
					eq = 1;
				}
			}
			if (is_export && eq)
				write(1, "\"", g_global_data.out_fd);
			ft_putstr_fd("\n", g_global_data.out_fd);
		}
		g_global_data.errno_cp = 0;
	}
}
