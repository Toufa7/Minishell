/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   driver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchfa <abouchfa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 06:00:08 by abouchfa          #+#    #+#             */
/*   Updated: 2022/08/25 06:07:06 by abouchfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_bool	check_builtin(t_pipe_data *pipe_data)
{
	if (!ft_strcmp("cd", pipe_data->command))
	{
		pipe_files_prep(pipe_data, TRUE);
		if (!g_glbl_data.redirection_error)
			mcd(*(pipe_data->argv + 1));
	}
	else if (!ft_strcmp("echo", pipe_data->command))
	{
		pipe_files_prep(pipe_data, TRUE);
		if (!g_glbl_data.redirection_error)
			mecho(pipe_data->argv + 1);
	}
	else if (!ft_strcmp("env", pipe_data->command))
	{
		pipe_files_prep(pipe_data, TRUE);
		if (!g_glbl_data.redirection_error)
			menv(pipe_data->argv + 1, NULL, FALSE);
	}
	else if (!ft_strcmp("exit", pipe_data->command))
	{
		pipe_files_prep(pipe_data, TRUE);
		if (!g_glbl_data.redirection_error)
			mexit(pipe_data->argv + 1);
	}
	else if (!ft_strcmp("export", pipe_data->command))
	{
		pipe_files_prep(pipe_data, TRUE);
		if (!g_glbl_data.redirection_error)
			mexport(pipe_data->argv + 1);
	}
	else if (!ft_strcmp("pwd", pipe_data->command))
	{
		pipe_files_prep(pipe_data, TRUE);
		if (!g_glbl_data.redirection_error)
			mpwd();
	}
	else if (!ft_strcmp("unset", pipe_data->command))
	{
		pipe_files_prep(pipe_data, TRUE);
		if (!g_glbl_data.redirection_error)
			munset(pipe_data->argv + 1);
	}
	else
		return (FALSE);
	ft_close(g_glbl_data.in_fd, 1);
	ft_close(g_glbl_data.out_fd, 1);
	g_glbl_data.in_fd = 0;
	g_glbl_data.out_fd = 1;
	return (TRUE);
}
