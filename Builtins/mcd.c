/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mcd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchfa <abouchfa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 16:19:40 by otoufah           #+#    #+#             */
/*   Updated: 2022/08/28 10:37:32 by abouchfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_error(char *path)
{
	ft_putstr_fd("cd: ", 2);
	ft_putstr_fd(path, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd("\n", 2);
	g_data.errno_cp = errno;
}

void	update_oldpwd(void)
{
	char	buff[PATH_MAX];
	int		i;

	i = get_var_index("OLDPWD=");
	if (getcwd(buff, sizeof(buff)) != NULL)
	{
		if (i != -1)
		{
			//free(g_data.envp[i]);
			g_data.envp[i] = ft_strjoin("OLDPWD=", buff);
		}
	}
}

void	update_pwd(void)
{
	int		i;
	char	buff[PATH_MAX];

	i = get_var_index("PWD=");
	if (getcwd(buff, sizeof(buff)) != NULL)
	{
		if (i != -1)
		{
			//free(g_data.envp[i]);
			g_data.envp[i] = ft_strjoin("PWD=", buff);
		}
	}
	else
	{
		ft_putstr_fd("cd: error retrieving current directory: getcwd: ", 2);
		ft_putstr_fd("cannot access parent directories", 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
}

void	mcd(char *path)
{
	if (!path)
		return ;
	update_oldpwd();
	if (chdir(path) != 0)
		print_error(path);
	else
	{
		g_data.errno_cp = 0;
		update_pwd();
	}
}
