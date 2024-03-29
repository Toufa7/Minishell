/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchfa <abouchfa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 06:20:42 by abouchfa          #+#    #+#             */
/*   Updated: 2022/09/03 03:47:52 by abouchfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	read_herdoc(char *delimiter)
{
	char	*line;
	char	*without_d_s;
	char	*expand;
	int		fd;

	fd = open_heredoc_file(FALSE);
	line = readline("> ");
	without_d_s = remove_quotes(ft_strdup(delimiter, TRUE));
	expand = NULL;
	while (!line || ft_strcmp(line, without_d_s))
	{
		if (line)
		{
			expand = get_env_in_herdoc(line, FALSE, delimiter);
			write(fd, expand, ft_strlen(expand));
			write(fd, "\n", 1);
			free_str(expand);
		}
		else
			break ;
		line = readline("> ");
	}
	free_str(line);
	ft_close(fd, 3);
}

void	herdocs(t_pipe *pipe_data)
{
	int		j;
	int		id;

	j = -1;
	id = ft_fork();
	if (id != 0)
		g_data.heredoc_file = ft_strjoin("/tmp/heredoc_file", ft_itoa(id));
	else
		exit(0);
	id = ft_fork();
	if (id == 0)
	{
		signal(SIGINT, herdoc_sigint);
		while (pipe_data->delimiter && pipe_data->delimiter[++j])
			read_herdoc(pipe_data->delimiter[j]);
		exit(0);
	}
	signal(SIGINT, SIG_IGN);
	waitpid(id, &g_data.errno_cp, 0);
	signal(SIGINT, parent_sigint);
}

void	sig_wait(t_pipe **pipes)
{
	int	i;

	i = -1;
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	while (pipes[++i] && (g_data.size > 1
			|| check_builtin(pipes[0]) == -1))
	{
		if (i == 0)
		{
			waitpid(g_data.last_child_id, &g_data.errno_cp, 0);
			if (WIFEXITED(g_data.errno_cp))
				g_data.errno_cp = WEXITSTATUS(g_data.errno_cp);
			else if (g_data.errno_cp == 3 || g_data.errno_cp == 2)
				g_data.errno_cp += 128;
		}
		else
			waitpid(-1, NULL, 0);
	}
	signal(SIGINT, parent_sigint);
	signal(SIGQUIT, SIG_IGN);
}

void	execs(t_pipe *pipe_data, int builtin_nb)
{
	if (builtin_nb != -1)
	{
		exec_builtin(builtin_nb, pipe_data);
		exit(0);
	}
	else if (pipe_data->cmd_path)
	{
		if (execve(pipe_data->cmd_path, pipe_data->argv, g_data.envp) == -1)
		{
			ft_putstr_fd("Mini: ", 2);
			ft_putstr_fd(strerror(errno), 2);
			ft_putstr_fd("\n", 2);
			exit(errno);
		}
	}
	else
		exit(0);
}

t_bool	check_file_errors(char *path, t_bool is_builtin)
{
	if (path && (path[0] == '$' || (path[0] == '"' && path[0] == '$')))
	{
		g_data.redirection_error = TRUE;
		g_data.errno_cp = 1;
		if (path[0] == '$' && path[1])
		{
			ft_putstr_fd("Mini: ", 2);
			ft_putstr_fd(path, 2);
			ft_putstr_fd(" ambiguous redirect\n", 2);
		}
		else
			ft_putstr_fd("Mini: No such file or directory\n", 2);
		if (is_builtin)
			return (TRUE);
		else
			exit(1);
	}
	return (FALSE);
}
