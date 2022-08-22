#include "../minishell.h"

void ft_close(int n, int s)
{
	(void) s;
	if (n > 2)
		close(n);
}

void	herdoc_signals(int sig)
{
	(void) sig;
	exit(1);
}

bool	get_herdoc(t_pipe_data *pipe_data)
{
	char	*line;
	char	*expand;
	int		fd;
	int		j;
	int		exit_status;
	int id;

	j = -1;
	global_data.is_in_herdoc = TRUE;
	id = fork();
	if (id == 0)
	{
		signal(SIGINT, herdoc_signals);
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
					break;
				line = readline("> ");
			}
			free_str(line);
			ft_close(fd, 3);
		}
		exit(0);
	}
	waitpid(-1, &exit_status, 0);
	global_data.is_in_herdoc = FALSE;
	return (exit_status);
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
					exit(126);
				}
				else
				{
					perror(pipe_data->command);
					exit(errno);
				}
			}
		}
	}
	else
		pipe_data->cmd_path = get_cmd_path(pipe_data->command, execps_paths);
	free_arr((void **) execps_paths);
}

void	pipe_files_prep(t_pipe_data *pipe_data, bool is_builtin)
{
	int	i;
	int fd;

	i = -1;
	while (pipe_data->redirections && pipe_data->redirections[++i])
	{
		if (pipe_data->redirections[i]->type == INFILE)
		{
			if (access(pipe_data->redirections[i]->path, F_OK) || access(pipe_data->redirections[i]->path, R_OK))
			{
				perror(pipe_data->redirections[i]->path);
				if (!is_builtin)
					exit(errno);
				global_data.errno_cp = errno;
			}
			fd = open(pipe_data->redirections[i]->path, O_RDONLY);
			pipe_data->in_fd_set = TRUE;
			if (!pipe_data->is_herdoc && !is_builtin)
				dup2(fd, 0);
			ft_close(fd, 8);
		}
		else if (pipe_data->redirections[i]->type == OUTFILE)
		{
			fd = open(pipe_data->redirections[i]->path,
						O_CREAT | O_WRONLY | O_TRUNC, 0777);
			pipe_data->out_fd_set = TRUE;
			if (!is_builtin || global_data.size > 1)
			{
				dup2(fd, 1);
				ft_close(fd, 10);
			}
			else
				global_data.out_fd = fd;
		}
		else if (pipe_data->redirections[i]->type == APPENDFILE)
		{
			fd = open(pipe_data->redirections[i]->path,
						O_CREAT | O_WRONLY | O_APPEND, 0777);
			pipe_data->out_fd_set = TRUE;
			if (!is_builtin || global_data.size > 1)
			{
				dup2(fd, 1);
				ft_close(fd, 9);
			}
			else
				global_data.out_fd = fd;
		}
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
	ft_close(global_data.in_fd, 1);
	ft_close(global_data.out_fd, 1);
	global_data.in_fd = 0;
	global_data.out_fd = 1;
	return TRUE;
}

void	child_process(t_pipe_data *pipe_data, int index)
{
	int fd;

	global_data.last_child_id = fork();
	if (global_data.last_child_id == 0)
	{
		pipe_files_prep(pipe_data, FALSE);
		validate_cmd(pipe_data);
		if (!pipe_data->cmd_path)
			exit(1);
		if (pipe_data->is_herdoc)
		{
			fd = open("/tmp/herdoc", O_RDWR, 0777);
			dup2(global_data.cmd_pipe_fds[1], 1);
			dup2(fd, 0);
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

	i = -1;
	while (pipes_data[global_data.size])
		global_data.size++;
	while (pipes_data[++i])
	{
		if (pipes_data[i]->is_herdoc)
		{
			if (!get_herdoc(pipes_data[i]))
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