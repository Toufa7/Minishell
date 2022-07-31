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


void	herdoc(t_pipe_data **pipe_data)
{
	char	*line;
	int		i;
	int		j;

	i = -1;
	while (pipe_data[++i])
	{
		j = -1;
		if (pipe_data[i]->delimiter)
		{
			while (pipe_data[i]->delimiter[++j])
			{
				pipe(pipe_data[i]->here_doc_pipe_fds);
				line = get_next_line(0);
				while (line == NULL || ft_strcmp(line, pipe_data[i]->delimiter[j]))
				{
					if (line)
					{
						write(pipe_data[i]->here_doc_pipe_fds[1], line, ft_strlen(line));
						write(pipe_data[i]->here_doc_pipe_fds[1], "\n", 1);
						free_str(line);
					}
					line = get_next_line(0);
				}
				free_str(line);
			}
			
		}
	}
}

void	execution(t_pipe_data **pipe_data)
{
	int			i;
	int			j;
	int			input_fd;
	t_pipe_data	*pipe_data;

	i = -1;
	input_fd = -1;
	pipe_data = malloc(sizeof(t_pipe_data));
	if (!pipe_data)
		exit(errno);
	while (pipe_data[++i])
	{
		if (pipe_data[i + 1])
			pipe(pipe_data[i]->cmd_pipe_fds);
		child_process(i, input_fd, pipe_data[i]);
		close(pipe_data[i]->here_doc_pipe_fds[1]);
		close(pipe_data[i]->here_doc_pipe_fds[0]);
		close(pipe_data[i]->cmd_pipe_fds[1]);
		if (input_fd != -1)
			close(input_fd);
		input_fd = pipe_data[i]->cmd_pipe_fds[0];
	}
	close(input_fd);
	i = -1;
	while (pipe_data[++i])
		wait(NULL);
}
