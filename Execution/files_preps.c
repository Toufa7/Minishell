/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_preps.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchfa <abouchfa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 05:23:48 by abouchfa          #+#    #+#             */
/*   Updated: 2022/08/25 06:05:12 by abouchfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	in_file_prep(t_pipe_data *pipe_data, char *path, t_bool is_builtin)
{
	int	fd;

	if (access(path, F_OK) || access(path, R_OK))
	{
		g_global_data.errno_cp = errno;
		g_global_data.redirection_error = TRUE;
		perror(path);
		if (!is_builtin)
			exit(errno);
	}
	fd = open(path, O_RDONLY);
	pipe_data->in_fd_set = TRUE;
	if (!pipe_data->is_herdoc && !is_builtin)
		dup2(fd, 0);
	ft_close(fd, 8);
}

void	out_file_prep(t_pipe_data *pipe_data, char *path, t_bool is_builtin)
{
	int	fd;

	fd = open(path, O_CREAT | O_WRONLY | O_TRUNC, 0777);
	pipe_data->out_fd_set = TRUE;
	if (!is_builtin || g_global_data.size > 1)
	{
		dup2(fd, 1);
		ft_close(fd, 10);
	}
	else
		g_global_data.out_fd = fd;
}

void	append_file_prep(t_pipe_data *pipe_data, char *path, t_bool is_builtin)
{
	int	fd;

	fd = open(path, O_CREAT | O_WRONLY | O_APPEND, 0777);
	pipe_data->out_fd_set = TRUE;
	if (!is_builtin || g_global_data.size > 1)
	{
		dup2(fd, 1);
		ft_close(fd, 9);
	}
	else
		g_global_data.out_fd = fd;
}

void	pipe_files_prep(t_pipe_data *pipe_data, t_bool is_builtin)
{
	char	*path;
	int		i;

	i = -1;
	while (pipe_data->redirections && pipe_data->redirections[++i])
	{
		path = pipe_data->redirections[i]->path;
		if (path && path[0] == '$')
		{
			g_global_data.redirection_error = TRUE;
			g_global_data.errno_cp = 1;
			if (path[0] == '$' && path[1])
			{
				ft_putstr_fd(path, 2);
				ft_putstr_fd(": ambiguous redirect\n", 2);
			}
			else
				ft_putstr_fd(": No such file or directory\n", 2);
			if (is_builtin)
				break ;
			else
				exit(1);
		}
		if (pipe_data->redirections[i]->type == INFILE)
			in_file_prep(pipe_data, path, is_builtin);
		else if (pipe_data->redirections[i]->type == OUTFILE)
			out_file_prep(pipe_data, path, is_builtin);
		else if (pipe_data->redirections[i]->type == APPENDFILE)
			append_file_prep(pipe_data, path, is_builtin);
	}
}
