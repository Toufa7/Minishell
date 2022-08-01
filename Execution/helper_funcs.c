// #include "../minishell.h"

// void	get_herdoc(t_pipe_data *pipe_data)
// {
// 	char	*line;
// 	int		j;

// 	j = -1;
// 	while (pipe_data->delimiter[++j])
// 	{
// 		if (j > 0)
// 		{
// 			ft_close(global_data.here_doc_pipe_fds[1]);
// 			ft_close(global_data.here_doc_pipe_fds[0]);
// 		}
// 		pipe(global_data.here_doc_pipe_fds);
// 		line = get_next_line(0);
// 		while (line == NULL || ft_strcmp(line, pipe_data->delimiter[j]))
// 		{
// 			if (line)
// 			{
// 				write(global_data.here_doc_pipe_fds[1], line, ft_strlen(line));
// 				write(global_data.here_doc_pipe_fds[1], "\n", 1);
// 				free_str(line);
// 			}
// 			line = get_next_line(0);
// 		}
// 		free_str(line);
// 	}
// }

