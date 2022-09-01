/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   driver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchfa <abouchfa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 06:00:08 by abouchfa          #+#    #+#             */
/*   Updated: 2022/08/30 12:47:29 by abouchfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_builtin(t_pipe *pipe_data)
{
	if (!ft_strcmp("cd", pipe_data->command))
		return (1);
	else if (!ft_strcmp("echo", pipe_data->command))
		return (2);
	else if (!ft_strcmp("env", pipe_data->command))
		return (3);
	else if (!ft_strcmp("exit", pipe_data->command))
		return (4);
	else if (!ft_strcmp("export", pipe_data->command))
		return (5);
	else if (!ft_strcmp("pwd", pipe_data->command))
		return (6);
	else if (!ft_strcmp("unset", pipe_data->command))
		return (7);
	else
		return (-1);
}

void	exec_builtin(int builtin_nb, t_pipe *pipe_data)
{
	if (builtin_nb == 1 && !g_data.redirection_error)
		mcd(*(pipe_data->argv + 1));
	else if (builtin_nb == 2 && !g_data.redirection_error)
		mecho(pipe_data->argv + 1);
	else if (builtin_nb == 3 && !g_data.redirection_error)
		menv(pipe_data->argv + 1, NULL, FALSE);
	else if (builtin_nb == 4 && !g_data.redirection_error)
		mexit(pipe_data->argv + 1);
	else if (builtin_nb == 5 && !g_data.redirection_error)
		mexport(pipe_data->argv + 1);
	else if (builtin_nb == 6 && !g_data.redirection_error)
		mpwd();
	else if (builtin_nb == 7 && !g_data.redirection_error)
		munset(pipe_data->argv + 1);
	ft_close(g_data.in_fd, 1);
	ft_close(g_data.out_fd, 1);
	g_data.in_fd = 0;
	g_data.out_fd = 1;
}
