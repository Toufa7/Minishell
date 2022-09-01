/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchfa <abouchfa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 16:17:46 by otoufah           #+#    #+#             */
/*   Updated: 2022/09/01 01:49:40 by abouchfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	get_herdoc(t_pipe_data *pipe_data)
{
	char	*line;
	char	*expand;
	int		fd;
	int		j;
	int		id;

	j = -1;
	id = fork();
	if (id == 0)
	{
		signal(SIGINT, herdoc_sigint);
		while (pipe_data->delimiter && pipe_data->delimiter[++j])
		{
			fd = open("/tmp/herdoc", O_CREAT | O_RDWR | O_TRUNC, 0777);
			line = readline("> ");
			expand = NULL;
			while (!line || ft_strcmp(line, pipe_data->delimiter[j]))
			{
				if (line)
				{
					expand = get_env_in_herdoc(line, FALSE);
					write(fd, expand, ft_strlen(expand));
					write(fd, "\n", 1);
					free_str(expand);
				}
				else
					break ;
				line = readline("> ");
			}
			free_str(line);
			ft_close(fd, 3);
		}
		exit(0);
	}
	signal(SIGINT, SIG_IGN);
	waitpid(id, &g_data.errno_cp, 0);
	signal(SIGINT, parent_sigint);
}

void	child_process(t_pipe_data *pipe_data, int pipe_nb, int builtin_nb)
{
	int fd;

	g_data.last_child_id = fork();
	if (g_data.last_child_id == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		pipe_files_prep(pipe_data, builtin_nb != -1);
		if (builtin_nb == -1)
			validate_cmd(pipe_data);
		if (pipe_data->is_herdoc)
		{
			fd = open("/tmp/herdoc", O_RDWR, 0004);
			dup2(g_data.cmd_pipe_fds[1], 1);
			dup2(fd, 0);
			ft_close(fd, 1);
		}
		else if (g_data.pre_pipe_infd != -1 && !pipe_data->in_fd_set)
			dup2(g_data.pre_pipe_infd, 0);
		if (g_data.size != pipe_nb + 1 && !pipe_data->out_fd_set)
			dup2(g_data.cmd_pipe_fds[1], 1);
		ft_close(g_data.cmd_pipe_fds[1], 5);
		ft_close(g_data.cmd_pipe_fds[0], 4);
		if (builtin_nb != -1)
		{
			exec_builtin(builtin_nb, pipe_data);
			exit(0);
		}
		else if (pipe_data->cmd_path)
		{
			if (execve(pipe_data->cmd_path, pipe_data->argv, g_data.envp) == -1)
			{
				ft_putstr_fd(strerror(errno), 2);
				ft_putstr_fd("\n", 2);
				exit(errno);
			}
		}
		else
			exit(0);
	}
}

void	exec_pipe(t_pipe_data *pipe_data, int index)
{
	int	builtin_nb;

	builtin_nb = check_builtin(pipe_data);
	if (g_data.size == 1 && builtin_nb != -1)
	{
		pipe_files_prep(pipe_data, TRUE);
		exec_builtin(builtin_nb, pipe_data);
	}
	else
	{
		if (g_data.size != index + 1)
			pipe(g_data.cmd_pipe_fds);
		child_process(pipe_data, index, builtin_nb);
		ft_close(g_data.cmd_pipe_fds[1], 5);
		ft_close(g_data.pre_pipe_infd, 2);
		g_data.pre_pipe_infd = g_data.cmd_pipe_fds[0];
	}
}

void	execution(t_pipe_data **pipes_data)
{
	int		i;

	while (pipes_data[g_data.size])
		g_data.size++;
	i = -1;
	while (pipes_data[++i])
	{
		g_data.errno_cp = 0;
		if (pipes_data[i]->is_herdoc)
		{
			get_herdoc(pipes_data[i]);
			if (!g_data.errno_cp)
				exec_pipe(pipes_data[i], i);
		}
	}
	i = -1;
	while (pipes_data[++i])
		if (!pipes_data[i]->is_herdoc)
			exec_pipe(pipes_data[i], i);
	ft_close(g_data.pre_pipe_infd, 1);
	i = -1;
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	while (pipes_data[++i] && (g_data.size > 1 || check_builtin(pipes_data[0]) == -1))
	{
		if (i == 0)
		{
			waitpid(g_data.last_child_id, &g_data.errno_cp, 0);
			if (WIFEXITED(g_data.errno_cp))
				g_data.errno_cp = WEXITSTATUS(g_data.errno_cp);
			else if (g_data.errno_cp == 3 || g_data.errno_cp == 2)
				g_data.errno_cp += 128;
		}
		else
			waitpid(-1, NULL, 0);
	}
	signal(SIGINT, parent_sigint);
	signal(SIGQUIT, SIG_IGN);
}