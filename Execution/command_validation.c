/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_validation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchfa <abouchfa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 19:09:57 by abouchfa          #+#    #+#             */
/*   Updated: 2022/08/28 15:58:08 by abouchfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*put_cmd_status(int status, char *cmd_path, char *cmd)
{
	if (status)
	{
		if (status == 1 && cmd && cmd[0] != '$')
		{
			ft_putstr_fd(cmd, 2);
			ft_putstr_fd(": command not found\n", 2);
			exit(127);
		}
		else if (cmd && cmd[0] != '$')
		{
			ft_putstr_fd(cmd, 2);
			ft_putstr_fd(": permission denied\n", 2);
			exit(126);
		}
		return (NULL);
	}
	else
		return (cmd_path);
}

char	*get_cmd_path(char *cmd, char **exec_programs_dirs)
{
	char	*cmd_path;
	char	*temp;
	int		i;
	int		status;

	i = -1;
	status = 1;
	cmd_path = NULL;
	temp = NULL;
	while (exec_programs_dirs[++i] && cmd && cmd[0] && status)
	{
		temp = ft_strjoin(exec_programs_dirs[i], "/");
		cmd_path = ft_strjoin(temp, cmd);
		if (access(cmd_path, F_OK))
			status = 1;
		else if (access(cmd_path, X_OK))
			status = 2;
		else
			status = 0;
	}
	return (put_cmd_status(status, cmd_path, cmd));
}

void	check_cmd_path(t_pipe_data *pipe_data)
{
	struct stat	statbuf;

	if (stat(pipe_data->command, &statbuf) == 0)
	{
		if (!S_ISDIR(statbuf.st_mode) && !access(pipe_data->command, F_OK)
			&& !access(pipe_data->command, X_OK))
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

void	check_command_name(t_pipe_data *pipe_data)
{
	int		i;
	char	*path_var;
	char	**execps_paths;

	i = -1;
	execps_paths = NULL;
	path_var = NULL;
	i = get_var_index("PATH=");
	if (i != -1)
	{
		execps_paths = ft_split(g_data.envp[i] + 5, ':');
		pipe_data->cmd_path = get_cmd_path(pipe_data->command, execps_paths);
	}
	else
	{
		ft_putstr_fd(pipe_data->command, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		exit(127);
	}
}

void	validate_cmd(t_pipe_data *pipe_data)
{
	if (ft_strchr(pipe_data->command, '/'))
		check_cmd_path(pipe_data);
	else
		check_command_name(pipe_data);
}
