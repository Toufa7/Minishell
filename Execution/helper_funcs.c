#include "../minishell.h"

void	get_herdoc(t_pipe_data *pipe_data)
{
	char	*line;
	int		j;

	j = -1;
	while (pipe_data->delimiter[++j])
	{
		if (j > 0)
		{
			close(global_data.here_doc_pipe_fds[1]);
			close(global_data.here_doc_pipe_fds[0]);
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

char	*get_cmd(char *str)
{
	char	*cmd;
	int		i;
	int		j;

	i = 0;
	while (str[i] && str[i] != ' ')
		i++;
	cmd = malloc(sizeof(char) * i + 1);
	if (!cmd)
		return (NULL);
	j = -1;
	while (++j < i)
		cmd[j] = str[j];
	cmd[j] = 0;
	return (cmd);
}