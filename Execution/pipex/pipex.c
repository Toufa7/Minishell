#include "../../minishell.h"

void	validate_input(t_pipe_data *pipe_data, t_input *input)
{
	int		i;
	char	*cmd;
	char	**exec_programs_dirs;
	char	*path_var;

	i = -1;
	exec_programs_dirs = NULL;
	path_var = NULL;
	while (genv[++i])
	{
		path_var = ft_strnstr(genv[i], "PATH=", 5);
		if (path_var)
		{
			path_var = path_var + 5;
			break;
		}
	}
	if (pipe_data->infile_path)
		pipe_data->infile_status = validate_infile(pipe_data->infile_path);
	if (path_var)
		exec_programs_dirs = ft_split(path_var, ':');
	validate_cmd(pipe_data, input);
	free_arr(exec_programs_dirs);
}

void	driver(t_pipe_data *pipe_data, char *envp[])
{
	int	i;
	int	input_fd;

	i = -1;
	input_fd = -1;
	while (++i < pipe_data->cmds_size)
	{
		if (i + 1 != pipe_data->cmds_size)
			pipe(pipe_data->cmd_pipe_fds);
		child_process(i, input_fd, pipe_data, envp);
		if (i == 0 && pipe_data->is_heredoc)
		{
			close(pipe_data->here_doc_pipe_fds[1]);
			close(pipe_data->here_doc_pipe_fds[0]);
		}
		close(pipe_data->cmd_pipe_fds[1]);
		if (input_fd != -1)
			close(input_fd);
		input_fd = pipe_data->cmd_pipe_fds[0];
	}
	close(input_fd);
	i = -1;
	while (++i < pipe_data->cmds_size)
		wait(NULL);
}

void	check_heredoc(t_pipe_data *pipe_data, char *argv[], int argc)
{
	if (!ft_strncmp(argv[1], "here_doc", 9))
	{
		pipe_data->is_heredoc = 1;
		pipe_data->heredoc_limiter = argv[2];
		pipe_data->cmds_size = argc - 4;
		pipe(pipe_data->here_doc_pipe_fds);
		get_herdoc(pipe_data);
	}
	else
	{
		pipe_data->is_heredoc = 0;
		pipe_data->infile_path = argv[1];
		pipe_data->cmds_size = argc - 3;
	}
}

void	set_pipe_data(t_pipe_data *pipe_data, t_input *input, int index)
{
	pipe_data->cmd_name = input->command[index];
	pipe_data->infile_path = input->in_files[index];
	pipe_data->heredoc_limiter = input->delimiter[index];
	pipe_data->cmd_name = input->command[index];
	pipe_data->outfile_path = input->out_files[index];
	validate_input(pipe_data, input);
}

void	execution(int argc, char *argv[], char *envp[], t_input *input)
{
	t_pipe_data	*pipe_data;
	int			i;

	pipe_data = malloc(sizeof(t_pipe_data));
	if (!pipe_data)
		exit(errno);
	i = -1;
	while (++i < input->size)
	{
		if (input->delimiter[i])
			set_pipe_data(pipe_data, input, index);
	}
	check_heredoc(pipe_data, argv, argc);
	driver(pipe_data, envp);
}
