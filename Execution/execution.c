#include "../minishell.h"

void ft_close(int n, int s)
{
	(void) s;
	//printf("---> n: %i | s: %i\n", n, s);
	if (n > 2)
		close(n);
}

void	get_herdoc(t_pipe_data *pipe_data)
{
	char	*line;
	int		j;

	j = -1;
	while (pipe_data->delimiter[++j])
	{
		if (j > 0)
		{
			ft_close(global_data.here_doc_pipe_fds[1], 4);
			ft_close(global_data.here_doc_pipe_fds[0], 4);
		}
		pipe(global_data.here_doc_pipe_fds);
		line = get_next_line(0);
		while (line == NULL || ft_strcmp(line, pipe_data->delimiter[j]))
		{
			if (line)
			{
				write(global_data.here_doc_pipe_fds[1], line, ft_strlen(line));
				write(global_data.here_doc_pipe_fds[1], "\n", 1);
				free_str(line);
			}
			line = get_next_line(0);
		}
		free_str(line);
	}
}

void	validate_cmd(t_pipe_data *pipe_data)
{
	int		i;
	char	**execps_paths;
	char	*path_var;

	i = -1;
	execps_paths = NULL;
	path_var = NULL;
	while (global_data.envp[++i])
	{
		path_var = ft_strnstr(global_data.envp[i], "PATH=", 5);
		if (path_var)
		{
			path_var = path_var + 5;
			execps_paths = ft_split(path_var, ':');
			break;
		}
	}
	if (ft_strchr(pipe_data->command, '/') || !execps_paths)
	{
		if (!access(pipe_data->command, F_OK) && !access(pipe_data->command, X_OK))
			pipe_data->cmd_path = pipe_data->command;
		else
			perror(pipe_data->command);
	}
	else
		pipe_data->cmd_path = get_cmd_path(pipe_data->command, execps_paths);
	free_arr(execps_paths);
}

void	pipe_files_prep(t_pipe_data *pipe_data)
{
	int	i;
	int fd;

	i = -1;
	while (pipe_data->in_files && pipe_data->in_files[++i])
	{
		if (validate_infile(pipe_data->in_files[i]))
		{
			fd = open(pipe_data->in_files[i], O_RDONLY);
			pipe_data->in_fd_set = TRUE;
			dup2(fd, 0);
			ft_close(fd, 8);
		}
	}
	i = -1;
	while (pipe_data->app_outfile && pipe_data->app_outfile[++i])
	{
		fd = open(pipe_data->app_outfile[i],
					O_CREAT | O_WRONLY | O_APPEND, 0777);
		dup2(fd, 1);
		pipe_data->out_fd_set = TRUE;
		ft_close(fd, 9);
	}
	i = -1;
	while (pipe_data->out_files && pipe_data->out_files[++i])
	{
		fd = open(pipe_data->out_files[i],
					O_CREAT | O_WRONLY | O_TRUNC, 0777);
		dup2(fd, 1);
		pipe_data->out_fd_set = TRUE;
		ft_close(fd, 10);
	}
}

void	exec_cmd(t_pipe_data *pipe_data)
{

	if (execve(pipe_data->cmd_path, pipe_data->options, global_data.envp) == -1)
	{
		ft_putstr_fd(strerror(errno), 2);
		exit(errno);
	}
}

void	exec_pipe(t_pipe_data *pipe_data, bool is_last)
{
	validate_cmd(pipe_data);
	if (!pipe_data->cmd_path)
		return ;
	if (!is_last)
		pipe(global_data.cmd_pipe_fds);
	if (fork() == 0)
	{
		pipe_files_prep(pipe_data);
		if (pipe_data->is_herdoc)
		{
			get_herdoc(pipe_data);
			dup2(global_data.here_doc_pipe_fds[0], 0);
			ft_close(global_data.here_doc_pipe_fds[1], 7);
			ft_close(global_data.here_doc_pipe_fds[0], 6);
		}
		else if (!pipe_data->in_fd_set && global_data.pre_pipe_infd != -1)
			dup2(global_data.pre_pipe_infd, 0);
		if (!is_last && !pipe_data->out_fd_set)
			dup2(global_data.cmd_pipe_fds[1], 1);
		ft_close(global_data.cmd_pipe_fds[1], 5);
		ft_close(global_data.cmd_pipe_fds[0], 4);
		if (global_data.pre_pipe_infd != -1)
			ft_close(global_data.pre_pipe_infd, 3);
		exec_cmd(pipe_data);
	}
	ft_close(global_data.cmd_pipe_fds[1], 5);
	if (global_data.pre_pipe_infd != -1)
			ft_close(global_data.pre_pipe_infd, 2);
	global_data.pre_pipe_infd = global_data.cmd_pipe_fds[0];
}

void	execution(t_pipe_data **pipes_data)
{
	int		i;

	if (global_data.err == 1)
		return ;
	i = -1;
	global_data.pre_pipe_infd = -1;
	global_data.pre_pipe_infd = -1;
	while (pipes_data[++i])
		if (pipes_data[i]->is_herdoc)
			exec_pipe(pipes_data[i], !pipes_data[i + 1]);
	i = -1;
	while (pipes_data[++i])
		if (!pipes_data[i]->is_herdoc)
			exec_pipe(pipes_data[i], !pipes_data[i + 1]);
	if (global_data.pre_pipe_infd != -1)
		ft_close(global_data.pre_pipe_infd, 1);
	i = -1;
	while (pipes_data[++i])
		wait(NULL);
}