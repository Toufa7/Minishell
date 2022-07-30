#include "../../minishell.h"

void	validate_input(t_pipe_data *pipe_data, t_input *input)
{
	int		i;
	char	*cmd;
	char	**execps_paths;
	char	*path_var;

	i = -1;
	execps_paths = NULL;
	path_var = NULL;
	while (genv[++i])
	{
		path_var = ft_strnstr(genv[i], "PATH=", 5);
		if (path_var)
		{
			path_var = path_var + 5;
			execps_paths = ft_split(path_var, ':');
			break;
		}
	}
	validate_infile(pipe_data->infile_path);		
	validate_cmd(pipe_data, execps_paths);
	free_arr(execps_paths);
}

void	set_pipe_data(t_pipe_data *pipe_data, t_input *input, int index)
{
	pipe_data->cmd_name = input->command[index];
	pipe_data->infile_path = input->in_files[index];
	pipe_data->heredoc_limiter = input->delimiter[index];
	pipe_data->cmd_name = input->command[index];
	pipe_data->red_outfile_path = input->out_files[index];
	pipe_data->app_infile_path = input->app_outfile[index];
	validate_input(pipe_data, input);
}

void	execution(t_input *input)
{
	t_pipe_data	*pipe_data;
	int			i;
	int			input_fd;

	i = -1;
	input_fd = -1;
	pipe_data = malloc(sizeof(t_pipe_data));
	if (!pipe_data)
		exit(errno);
	while (++i < input->size)
	{
		if (input->delimiter[i])
		{
			set_pipe_data(pipe_data, input, i);
			pipe(pipe_data->here_doc_pipe_fds);
			get_herdoc(pipe_data);
			if (i + 1 != input->size)
				pipe(pipe_data->cmd_pipe_fds);
			child_process(i, input_fd, pipe_data);
			close(pipe_data->here_doc_pipe_fds[1]);
			close(pipe_data->here_doc_pipe_fds[0]);
			close(pipe_data->cmd_pipe_fds[1]);
			if (input_fd != -1)
				close(input_fd);
			input_fd = pipe_data->cmd_pipe_fds[0];
		}
	}
	close(input_fd);
	i = -1;
	while (++i < input->size)
		wait(NULL);
}
