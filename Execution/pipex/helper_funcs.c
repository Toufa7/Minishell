#include "../../minishell.h"

void	ft_free_str(char *str)
{
	if (str)
		free(str);
}

void	ft_free_arr(char **arr)
{
	int	i;

	i = -1;
	while (arr && arr[++i])
		ft_free_str(arr[i]);
	if (arr)
		free(arr);
}

void	get_herdoc(t_pipe_data *pipe_data)
{
	char	*line;

	line = get_next_line(0);
	while (line == NULL || ft_strcmp(line, pipe_data->heredoc_limiter))
	{
		if (line)
		{
			write(pipe_data->here_doc_pipe_fds[1], line, ft_strlen(line));
			write(pipe_data->here_doc_pipe_fds[1], "\n", 1);
			ft_free_str(line);
		}
		line = get_next_line(0);
	}
	ft_free_str(line);
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
