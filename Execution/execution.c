/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchfa <abouchfa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 16:17:46 by otoufah           #+#    #+#             */
/*   Updated: 2022/09/03 03:47:05 by abouchfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	child_process(t_pipe *pipe_data, int pipe_nb, int builtin_nb)
{
	int	fd;

	g_data.last_child_id = fork();
	if (g_data.last_child_id == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		files_redirections(pipe_data, builtin_nb != -1);
		if (builtin_nb == -1)
			validate_cmd(pipe_data);
		if (pipe_data->is_herdoc && g_data.is_heredoc_last)
		{
			fd = open_heredoc_file(TRUE);
			dup2(fd, 0);
			ft_close(fd, 1);
		}
		else if (g_data.pre_pipe_infd != -1 && !pipe_data->in_fd_set)
			dup2(g_data.pre_pipe_infd, 0);
		if (g_data.size != pipe_nb + 1 && !pipe_data->out_fd_set)
			dup2(pipe_data->cmd_pipe_fds[1], 1);
		ft_close(pipe_data->cmd_pipe_fds[1], 5);
		ft_close(pipe_data->cmd_pipe_fds[0], 4);
		execs(pipe_data, builtin_nb);
	}
}

void	exec_pipe(t_pipe *pipe_data, int pipe_nb)
{
	int	builtin_nb;

	builtin_nb = check_builtin(pipe_data);
	if (g_data.size == 1 && builtin_nb != -1)
	{
		files_redirections(pipe_data, TRUE);
		exec_builtin(builtin_nb, pipe_data);
	}
	else
	{
		if (g_data.size != pipe_nb + 1)
			pipe(pipe_data->cmd_pipe_fds);
		child_process(pipe_data, pipe_nb, builtin_nb);
		ft_close(pipe_data->cmd_pipe_fds[1], 5);
		ft_close(g_data.pre_pipe_infd, 3);
	}
}

void	heredoc_iterate(t_pipe **pipes)
{
	int	i;

	i = -1;
	while (pipes[++i])
	{
		g_data.errno_cp = 0;
		if (pipes[i]->is_herdoc)
		{
			g_data.pre_pipe_infd = -1;
			if (i > 0)
				g_data.pre_pipe_infd = pipes[i - 1]->cmd_pipe_fds[0];
			herdocs(pipes[i]);
			if (g_data.errno_cp)
				break ;
			exec_pipe(pipes[i], i);
		}
	}
}

void	execution(t_pipe **pipes)
{
	int		i;

	i = -1;
	g_data.errno_cp = 0;
	heredoc_iterate(pipes);
	while (pipes[++i] && g_data.errno_cp == 0)
	{
		if (!pipes[i]->is_herdoc)
		{
			g_data.pre_pipe_infd = -1;
			if (i > 0)
				g_data.pre_pipe_infd = pipes[i - 1]->cmd_pipe_fds[0];
			exec_pipe(pipes[i], i);
		}
	}
	ft_close(g_data.pre_pipe_infd, 1);
	sig_wait(pipes);
}
