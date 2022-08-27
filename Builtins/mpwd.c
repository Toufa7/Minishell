/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mpwd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchfa <abouchfa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 16:20:03 by otoufah           #+#    #+#             */
/*   Updated: 2022/08/27 16:01:22 by abouchfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	mpwd(void)
{
	char	buff[PATH_MAX];
	char	*tmp;

	if (getcwd(buff, sizeof(buff)) != NULL)
	{
		ft_putstr_fd(buff, g_global_data.out_fd);
		ft_putstr_fd("\n", g_global_data.out_fd);
		g_global_data.errno_cp = 0;
	}
	else if (get_var_index("PWD=") != -1)
	{
		tmp = get_var_val(get_var_index("PWD="));
		ft_putstr_fd(tmp, g_global_data.out_fd);
		ft_putstr_fd("\n", g_global_data.out_fd);
		g_global_data.errno_cp = 0;
	}
	else
	{
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
		g_global_data.errno_cp = errno;
	}
}
