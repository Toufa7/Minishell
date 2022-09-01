/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menv.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchfa <abouchfa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 16:19:50 by otoufah           #+#    #+#             */
/*   Updated: 2022/09/01 06:05:48 by abouchfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_var(char *var, char *prefix, t_bool is_export, t_bool *eq)
{
	int	j;

	j = -1;
	while (var[++j])
		if (var[j] == '=')
			break ;
	if (var[j] != '=' && !is_export)
		return ;
	j = -1;
	*eq = FALSE;
	ft_putstr_fd(prefix, g_data.out_fd);
	while (var[++j])
	{
		write(1, var + j, g_data.out_fd);
		if (var[j] == '=' && is_export && !*eq)
		{
			write(1, "\"", g_data.out_fd);
			*eq = TRUE;
		}
	}
	if (is_export && *eq)
		write(1, "\"", g_data.out_fd);
	ft_putstr_fd("\n", g_data.out_fd);
}

void	menv(char **argv, char *prefix, t_bool is_export)
{
	int		i;
	t_bool	eq;

	if (argv && *argv)
	{
		ft_putstr_fd("Mini: env: ", 2);
		ft_putstr_fd(*argv, 2);
		ft_putstr_fd(" No such file or directory\n", 2);
		g_data.errno_cp = 127;
	}
	else
	{
		eq = FALSE;
		i = -1;
		while (g_data.envp[++i])
			print_var(g_data.envp[i], prefix, is_export, &eq);
		g_data.errno_cp = 0;
	}
}
