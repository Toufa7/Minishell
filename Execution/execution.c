/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchfa <abouchfa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 16:00:14 by otoufah           #+#    #+#             */
/*   Updated: 2022/08/27 09:37:28 by abouchfa         ###   ########.fr       */
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
	sig_t	sig;

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
					expand = get_env_in_herdoc(line);
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
	waitpid(id, &global_data.errno_cp, 0);
	signal(SIGINT, parent_sigint);
}

void	child_process(t_pipe_data *pipe_data, int index)
{
	int	fd;

	global_data.last_child_id = fork();
	if (global_data.last_child_id == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		pipe_files_prep(pipe_data, FALSE);
		validate_cmd(pipe_data);
		if (pipe_data->is_herdoc)
		{
			fd = open("/tmp/herdoc", O_RDWR, 0004);
			dup2(global_data.cmd_pipe_fds[1], 1);
			dup2(fd, 0);
			ft_close(fd, 1);
		}
		else if (global_data.pre_pipe_infd != -1 && !pipe_data->in_fd_set)
			dup2(global_data.pre_pipe_infd, 0);
		if (global_data.size != index + 1 && !pipe_data->out_fd_set)
			dup2(global_data.cmd_pipe_fds[1], 1);
		ft_close(global_data.cmd_pipe_fds[1], 5);
		ft_close(global_data.cmd_pipe_fds[0], 4);
		if (check_builtin(pipe_data))
			exit(0);
		else if (execve(pipe_data->cmd_path, pipe_data->argv,
				global_data.envp) == -1)
		{
			ft_putstr_fd(strerror(errno), 2);
			exit(errno);
		}
	}
}

void	exec_pipe(t_pipe_data *pipe_data, int index)
{
	if (global_data.size > 1 || !check_builtin(pipe_data))
	{
		if (global_data.size != index + 1)
			pipe(global_data.cmd_pipe_fds);
		child_process(pipe_data, index);
		ft_close(global_data.cmd_pipe_fds[1], 5);
		ft_close(global_data.pre_pipe_infd, 2);
		global_data.pre_pipe_infd = global_data.cmd_pipe_fds[0];
	}
}

void	execution(t_pipe_data **pipes_data)
{
	int		i;

	while (pipes_data[global_data.size])
		global_data.size++;
	i = -1;
	while (pipes_data[++i])
	{
		global_data.errno_cp = 0;
		if (pipes_data[i]->is_herdoc)
		{
			get_herdoc(pipes_data[i]);
			if (!global_data.errno_cp)
				exec_pipe(pipes_data[i], i);
		}
	}
	i = -1;
	while (pipes_data[++i])
		if (!pipes_data[i]->is_herdoc)
			exec_pipe(pipes_data[i], i);
	ft_close(global_data.pre_pipe_infd, 1);
	i = -1;
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	while (pipes_data[++i])
	{
		if (i == 0)
		{
			waitpid(global_data.last_child_id, &global_data.errno_cp, 0);
			global_data.errno_cp %= 255;
		}
		else
			waitpid(-1, NULL, 0);
	}
	if (global_data.errno_cp == 3 || global_data.errno_cp == 2)
		global_data.errno_cp += 128;
	signal(SIGINT, parent_sigint);
	signal(SIGQUIT, SIG_IGN);
}
