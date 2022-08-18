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
	char	*expand;
	int		j;

	j = -1;
	global_data.is_in_herdoc = TRUE;
	while (pipe_data->delimiter[++j])
	{
		if (j > 0)
		{
			ft_close(global_data.here_doc_pipe_fds[1], 4);
			ft_close(global_data.here_doc_pipe_fds[0], 4);
		}
		pipe(global_data.here_doc_pipe_fds);
		line = readline("> ");
		expand = NULL;
		while (!line || ft_strcmp(line, pipe_data->delimiter[j]))
		{ 
			if (line)
			{
				expand = get_env_in_herdoc(line);
				write(global_data.here_doc_pipe_fds[1], expand, ft_strlen(expand));
				write(global_data.here_doc_pipe_fds[1], "\n", 1);
				free_str(expand);
			}
			else
				break;
			line = readline("> ");
		}
		free_str(line);
	}
}

void	validate_cmd(t_pipe_data *pipe_data)
{
	int		i;
	char	**execps_paths;
	char	*path_var;
	struct	stat statbuf;

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
		if (stat(pipe_data->command, &statbuf) == 0)
		{
			if (!S_ISDIR(statbuf.st_mode) && !access(pipe_data->command, F_OK) && !access(pipe_data->command, X_OK))
				pipe_data->cmd_path = pipe_data->command;
			else
			{
				if (S_ISDIR(statbuf.st_mode))
				{
					ft_putstr_fd(pipe_data->command, 2);
					ft_putstr_fd(": is a directory\n", 2);
					global_data.errno_cp = 126;
				}
				else
				{
					perror(pipe_data->command);
					global_data.errno_cp = errno;
				}
			}
		}
	}
	else
		pipe_data->cmd_path = get_cmd_path(pipe_data->command, execps_paths);
	free_arr(execps_paths);
}

void	pipe_files_prep(t_pipe_data *pipe_data, bool is_builtin)
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
			if (!pipe_data->is_herdoc && !is_builtin)
				dup2(fd, 0);
			ft_close(fd, 8);
		}
	}
	i = -1;
	while (pipe_data->app_outfile && pipe_data->app_outfile[++i])
	{
		fd = open(pipe_data->app_outfile[i],
					O_CREAT | O_WRONLY | O_APPEND, 0777);
		pipe_data->out_fd_set = TRUE;
		if (!is_builtin)
			dup2(fd, 1);
		global_data.out_fd = fd;
		ft_close(fd, 9);
	}
	i = -1;
	while (pipe_data->out_files && pipe_data->out_files[++i])
	{
		fd = open(pipe_data->out_files[i],
					O_CREAT | O_WRONLY | O_TRUNC, 0777);
		pipe_data->out_fd_set = TRUE;
		if (!is_builtin)
			dup2(fd, 1);
		global_data.out_fd = fd;
		ft_close(fd, 10);
	}
}


bool	check_builtin(t_pipe_data *pipe_data)
{
	if (!ft_strcmp("cd", pipe_data->command))
	{
		pipe_files_prep(pipe_data, TRUE);
		mcd(*(pipe_data->argv + 1));
	}
	else if (!ft_strcmp("echo", pipe_data->command))
	{
		pipe_files_prep(pipe_data, TRUE);
		mecho(pipe_data->argv + 1);
	}
	else if (!ft_strcmp("env", pipe_data->command))
	{
		pipe_files_prep(pipe_data, TRUE);
		menv(pipe_data->argv + 1, NULL, FALSE);
	}
	else if (!ft_strcmp("exit", pipe_data->command))
	{
		pipe_files_prep(pipe_data, TRUE);
		mexit(pipe_data->argv + 1);
	}
	else if (!ft_strcmp("export", pipe_data->command))
	{
		pipe_files_prep(pipe_data, TRUE);
		mexport(pipe_data->argv + 1);
	}
	else if (!ft_strcmp("pwd", pipe_data->command))
	{
		pipe_files_prep(pipe_data, TRUE);
		mpwd();
	}
	else if (!ft_strcmp("unset", pipe_data->command))
	{
		pipe_files_prep(pipe_data, TRUE);
		munset(pipe_data->argv + 1);
	}
	else
		return FALSE;
	global_data.in_fd = 0;
	global_data.out_fd = 1;
	return TRUE;
}

void	child_process(t_pipe_data *pipe_data, int index)
{
	global_data.last_child_id = fork();
	if (global_data.last_child_id == 0)
	{
		pipe_files_prep(pipe_data, FALSE);
		if (pipe_data->is_herdoc)
		{
			dup2(global_data.cmd_pipe_fds[1], 1);
			dup2(global_data.here_doc_pipe_fds[0], 0);
			ft_close(global_data.here_doc_pipe_fds[1], 4);
			ft_close(global_data.here_doc_pipe_fds[0], 4);
		}
		else if (!pipe_data->in_fd_set && !pipe_data->is_herdoc)
			dup2(global_data.pre_pipe_infd, 0);
		if (global_data.size > index + 1 && !pipe_data->out_fd_set)
			dup2(global_data.cmd_pipe_fds[1], 1);
		ft_close(global_data.cmd_pipe_fds[1], 5);
		ft_close(global_data.cmd_pipe_fds[0], 4);
		if (check_builtin(pipe_data))
			exit(0);
		else
			execve(pipe_data->cmd_path, pipe_data->argv, global_data.envp);
	}
}

void	exec_pipe(t_pipe_data *pipe_data, int index)
{
	//printf("cmd: %s | size: %i\n", pipe_data->command, global_data.size);
	if (global_data.size > 1 || !check_builtin(pipe_data))
	{
		validate_cmd(pipe_data);
		if (!pipe_data->cmd_path)
			return ;
		if (global_data.size != index + 1)
			pipe(global_data.cmd_pipe_fds);
		child_process(pipe_data, index);
		ft_close(global_data.cmd_pipe_fds[1], 5);
		ft_close(global_data.pre_pipe_infd, 2);
		global_data.pre_pipe_infd = global_data.cmd_pipe_fds[0];
	}
	if (pipe_data->is_herdoc)
	{
		ft_close(global_data.here_doc_pipe_fds[1], 4);
		ft_close(global_data.here_doc_pipe_fds[0], 4);
	}
}

void	execution(t_pipe_data **pipes_data)
{
	int		i;

	i = -1;
	while (pipes_data[global_data.size])
		global_data.size++;
	while (pipes_data[++i])
	{
		if (pipes_data[i]->is_herdoc)
		{
			get_herdoc(pipes_data[i]);
			exec_pipe(pipes_data[i], i);
		}
	}
	i = -1;
	while (pipes_data[++i])
		if (!pipes_data[i]->is_herdoc)
			exec_pipe(pipes_data[i], i);
	ft_close(global_data.pre_pipe_infd, 1);
	i = -1;
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
}