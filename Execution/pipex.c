#include "../minishell.h"

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

bool	pipe_files_prep(t_pipe_data *pipe_data)
{
	int	i;
	int fd;
	bool out_file;

	i = -1;
	out_file = FALSE;
	while (pipe_data->in_files[++i])
	{
		if (validate_infile(pipe_data->in_files[i]))
		{
			fd = open(pipe_data->in_files[i], O_RDONLY);
			dup2(fd, 0);
			close(fd);
		}
	}
	i = -1;
	while (pipe_data->app_outfile[++i])
	{
		fd = open(pipe_data->app_outfile[i],
					O_CREAT | O_WRONLY | O_APPEND, 0777);
		dup2(fd, 1);
		close(fd);
	}
	i = -1;
	while (pipe_data->out_files[++i])
	{
		fd = open(pipe_data->out_files[i],
					O_CREAT | O_WRONLY | O_TRUNC, 0777);
		dup2(fd, 1);
		close(fd);
	}
}

void	exec_pipe(t_pipe_data *pipe_data, bool is_last)
{
	validate_cmd(pipe_data);
	if (!pipe_data->cmd_path)
		exit(errno);
	if (!is_last)
		pipe(global_data.cmd_pipe_fds);
	if (fork() == 0)
	{
		pipe_files_prep(pipe_data);
		if (pipe_data->is_herdoc)
			get_herdoc(pipe_data);
		if (pipe_data->is_herdoc)
		{
			dup2(global_data.here_doc_pipe_fds[0], 0);
			close(global_data.here_doc_pipe_fds[1]);
			close(global_data.here_doc_pipe_fds[0]);
		}
		if (!is_last)
		{
			pipe(global_data.cmd_pipe_fds);
			dup2(global_data.cmd_pipe_fds[1], 1);
		}
		close(global_data.cmd_pipe_fds[1]);
		close(global_data.cmd_pipe_fds[0]);
		if (global_data.pre_pipe_infd != -1)
			close(global_data.pre_pipe_infd);
	}
	close(global_data.cmd_pipe_fds[1]);
	if (global_data.pre_pipe_infd != -1)
			close(global_data.pre_pipe_infd);
	global_data.pre_pipe_infd = global_data.cmd_pipe_fds[0];
}

void	execution(t_pipe_data **pipes_data)
{
	int		i;

	i = -1;
	global_data.pre_pipe_infd = -1;
	global_data.pre_pipe_infd = -1;
	while (pipes_data[++i])
	{
		if (pipes_data[i]->is_herdoc)
			exec_pipe(pipes_data[i], !pipes_data[i + 1]);
	}
	if (global_data.pre_pipe_infd != -1)
		close(global_data.pre_pipe_infd);
	i = -1;
	while (pipes_data[++i])
		wait(NULL);
}
