/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchfa <abouchfa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 05:23:48 by abouchfa          #+#    #+#             */
/*   Updated: 2022/09/02 21:03:21 by abouchfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	in_file_prep(t_pipe *pipe_data, char *path, t_bool is_builtin)
{
	int	fd;

	if (access(path, F_OK) || access(path, R_OK))
	{
		g_data.errno_cp = errno;
		g_data.redirection_error = TRUE;
		ft_putstr_fd("Mini: ", 2);
		perror(path);
		if (!is_builtin || g_data.size > 1)
			exit(1);
	}
	else
	{
		fd = open(path, O_RDONLY);
		pipe_data->in_fd_set = TRUE;
		if (!pipe_data->is_herdoc && !is_builtin)
			dup2(fd, 0);
		ft_close(fd, 8);
	}
}	

void	out_file_prep(t_pipe *pipe_data, char *path, t_bool is_builtin)
{	
	int	fd;

	fd = open(path, O_CREAT | O_WRONLY | O_TRUNC, 0777);
	pipe_data->out_fd_set = TRUE;
	if (!is_builtin || g_data.size > 1)
	{
		dup2(fd, 1);
		ft_close(fd, 10);
	}
	else
		g_data.out_fd = fd;
}

void	append_file_prep(t_pipe *pipe_data, char *path, t_bool is_builtin)
{
	int	fd;

	fd = open(path, O_CREAT | O_WRONLY | O_APPEND, 0777);
	pipe_data->out_fd_set = TRUE;
	if (!is_builtin || g_data.size > 1)
	{
		dup2(fd, 1);
		ft_close(fd, 9);
	}
	else
		g_data.out_fd = fd;
}

t_bool	check_path(char *path, t_bool is_builtin)
{
	char		*folders;
	struct stat	statbuf;
	int			i;

	if (ft_strchr(path, '/') == 0)
		return (TRUE);
	i = ft_strlen(path);
	while (i != 0 && path[i] != '/')
		i--;
	folders = alloc(i + 2, "check_path");
	ft_strncpy(folders, path, i + 1);
	if (stat(folders, &statbuf) == -1)
	{
		ft_putstr_fd("Mini: ", 2);
		perror(path);
		if (is_builtin)
		{
			g_data.redirection_error = TRUE;
			g_data.errno_cp = 1;
			return (FALSE);
		}
		else
			exit(1);
	}
	return (TRUE);
}

void	files_redirections(t_pipe *pipe_data, t_bool is_builtin)
{
	char	*path;
	int		i;

	i = -1;
	while (pipe_data->redirections && pipe_data->redirections[++i])
	{
		path = pipe_data->redirections[i]->path;
		if (check_file_errors(path, is_builtin))
			break ;
		path = remove_quotes(pipe_data->redirections[i]->path);
		if (!check_path(path, is_builtin))
			break ;
		if (pipe_data->redirections[i]->type == INFILE)
			in_file_prep(pipe_data, path, is_builtin);
		else if (pipe_data->redirections[i]->type == OUTFILE)
			out_file_prep(pipe_data, path, is_builtin);
		else if (pipe_data->redirections[i]->type == APPENDFILE)
			append_file_prep(pipe_data, path, is_builtin);
	}
}
