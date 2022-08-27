/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mecho.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchfa <abouchfa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 16:19:46 by otoufah           #+#    #+#             */
/*   Updated: 2022/08/23 16:19:47 by otoufah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	mecho(char **argv)
{
	t_bool	new_line;
	t_bool	valid_arg;
	int		i;
	int		j;

	j = -1;
	new_line = FALSE;
	valid_arg = TRUE;
	while (argv[++j] && argv[j][0] == '-' && valid_arg)
	{
		i = 0;
		while (argv[j][++i])
		{
			if (argv[j][i] != 'n')
			{
				valid_arg = FALSE;
				break ;
			}
			else if (argv[j][i + 1] == '\0')
				new_line = TRUE;
		}
	}
	if (!valid_arg || i == 1)
		j--;
	while (argv[j])
	{
		ft_putstr_fd(argv[j++], g_global_data.out_fd);
		if (argv[j])
			ft_putstr_fd(" ", g_global_data.out_fd);
	}
	if (!new_line)
		ft_putstr_fd("\n", g_global_data.out_fd);
	g_global_data.errno_cp = 0;
}
