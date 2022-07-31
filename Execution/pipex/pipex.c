#include "../../minishell.h"

void	validate_input(t_pipe_data *pipe_data)
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
	validate_infile(pipe_data->in_files);		
	validate_cmd(pipe_data, execps_paths);
	free_arr(execps_paths);
}


void	herdoc(t_pipe_data **pipes_data)
{
	char	*line;
	int		i;
	int		j;

	i = -1;
	while (pipes_data[++i])
	{
		j = -1;
		if (pipes_data[i]->delimiter)
		{
			while (pipes_data[i]->delimiter[++j])
			{
				if (j > 0)
				{
					close(pipes_data[i]->here_doc_pipe_fds[1]);
					close(pipes_data[i]->here_doc_pipe_fds[0]);
				}
				pipe(pipes_data[i]->here_doc_pipe_fds);
				get_herdoc(pipes_data[i], pipes_data[i]->delimiter[j]);
			}
		}
	}
}

void	execution(t_pipe_data **pipes_data)
{
	int			i;
	int			j;
	int			input_fd;

	i = -1;
	input_fd = -1;
	while (pipes_data[++i])
	{
		if (pipes_data[i + 1])
			pipe(pipes_data[i]->cmd_pipe_fds);
		child_process(i, input_fd, pipes_data[i]);
		close(pipes_data[i]->here_doc_pipe_fds[1]);
		close(pipes_data[i]->here_doc_pipe_fds[0]);
		close(pipes_data[i]->cmd_pipe_fds[1]);
		if (input_fd != -1)
			close(input_fd);
		input_fd = pipes_data[i]->cmd_pipe_fds[0];
	}
	close(input_fd);
	i = -1;
	while (pipes_data[++i])
		wait(NULL);
}
