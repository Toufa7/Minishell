/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mpwd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchfa <abouchfa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 16:20:03 by otoufah           #+#    #+#             */
/*   Updated: 2022/08/23 16:20:04 by otoufah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	mpwd(void)
{
	char	buff[PATH_MAX];
	char	*tmp;

	if (getcwd(buff, sizeof(buff)) != NULL)
	{
		ft_putstr_fd(buff, global_data.out_fd);
		ft_putstr_fd("\n", global_data.out_fd);
		global_data.errno_cp = 0;
	}
	else if (get_var_index("PWD=") != -1)
	{
		tmp = get_var_val(get_var_index("PWD="), FALSE);
		ft_putstr_fd(tmp, global_data.out_fd);
		ft_putstr_fd("\n", global_data.out_fd);
		global_data.errno_cp = 0;
		free_str(tmp);
	}
	else
	{
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
		global_data.errno_cp = errno;
	}
}
