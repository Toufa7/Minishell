#include "../../minishell.h"

void	first_cmd_prep(t_pipe_data *pipe_data)
{
	int	fd;

	if (pipe_data->infile_status)
	{
		fd = open(pipe_data->infile_path, O_RDONLY);
		dup2(fd, 0);
		close(fd);
	}
	dup2(pipe_data->cmd_pipe_fds[1], 1);
}

void	ith_cmd_prep(int i, t_pipe_data *pipe_data, int input_fd)
{
	int	fd;

	if (i + 1 == pipe_data->cmds_size)
	{
		if (pipe_data->is_heredoc)
			fd = open(pipe_data->outfile_path,
					O_CREAT | O_WRONLY | O_APPEND, 0777);
		else
			fd = open(pipe_data->outfile_path,
					O_CREAT | O_WRONLY | O_TRUNC, 0777);
		dup2(fd, 1);
		close(fd);
	}
	else
		dup2(pipe_data->cmd_pipe_fds[1], 1);
	dup2(input_fd, 0);
}

void	exec_cmd(char *cmd, char *cmd_path, char **envp)
{
	char	**argv;

	argv = NULL;
	if (ft_strchr(cmd, '\''))
		argv = ft_split(cmd, '\'');
	else
		argv = ft_split(cmd, ' ');
	if (!cmd_path)
		exit(errno);
	else if (execve(cmd_path, argv, envp) == -1)
	{
		ft_putstr_fd(strerror(errno), 2);
		exit(errno);
	}
}

void	child_process(int i, int input_fd, t_pipe_data *pipe_data, char *envp[])
{
	if (fork() == 0)
	{
		if (i != 0)
			ith_cmd_prep(i, pipe_data, input_fd);
		else if (pipe_data->infile_status)
			first_cmd_prep(pipe_data);
		else if (pipe_data->is_heredoc)
		{
			dup2(pipe_data->cmd_pipe_fds[1], 1);
			dup2(pipe_data->here_doc_pipe_fds[0], 0);
			close(pipe_data->here_doc_pipe_fds[1]);
			close(pipe_data->here_doc_pipe_fds[0]);
		}
		close(pipe_data->cmd_pipe_fds[1]);
		close(pipe_data->cmd_pipe_fds[0]);
		if (input_fd != -1)
			close(input_fd);
		exec_cmd(pipe_data->cmds_names[i], pipe_data->cmds_paths[i], envp);
	}
}
