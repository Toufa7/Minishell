/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_validation_funcs.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchfa <abouchfa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 19:09:57 by abouchfa          #+#    #+#             */
/*   Updated: 2022/08/14 15:15:01 by abouchfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*put_cmd_status(int status, char *cmd_path, char *cmd)
{
	if (status)
	{
		ft_putstr_fd(cmd, 2);
		if (status == 1)
			ft_putstr_fd(" :command not found\n", 2);
		else
			ft_putstr_fd(" :permission denied\n", 2);
		global_data.errno_cp = 127;
		free_str(cmd_path);
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
		free_str(cmd_path);
		temp = ft_strjoin(exec_programs_dirs[i], "/");
		cmd_path = ft_strjoin(temp, cmd);
		if (access(cmd_path, F_OK))
			status = 1;
		else if (access(cmd_path, X_OK))
			status = 2;
		else
			status = 0;
		free_str(temp);
	}
	return (put_cmd_status(status, cmd_path, cmd));
}

int	validate_infile(char *infile_path)
{
	if (!access(infile_path, F_OK) && !access(infile_path, R_OK))
		return (1);
	perror(infile_path);
	global_data.errno_cp = errno;
	return (0);
}
