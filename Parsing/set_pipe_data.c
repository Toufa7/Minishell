/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_pipe_data.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchfa <abouchfa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 22:36:38 by otoufah           #+#    #+#             */
/*   Updated: 2022/08/30 17:46:59 by abouchfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	var_init(t_pipe_data *pipe_data)
{
	pipe_data->delimiter = NULL;
	pipe_data->redirections = NULL;
	pipe_data->command = NULL;
	pipe_data->argv = NULL;
	pipe_data->is_herdoc = FALSE;
	pipe_data->in_fd_set = FALSE;
	pipe_data->out_fd_set = FALSE;
}

t_redirections	*get_redirection(char *path, int type)
{
	t_redirections	*new_redrcs;
	int				i;

	i = 0;
	new_redrcs = alloc(sizeof(t_redirections), "get_redirection");
	new_redrcs->path = ft_strdup(path, TRUE);
	new_redrcs->type = type;
	return (new_redrcs);
}

void	set_pipe_data(t_pipe_data *pipe_data, t_pipe_token **pipe_tokens)
{
	int			i;
	int			j;
	char		*quotes;
	char		*replaced;

	i = -1;
	j = -1;
	var_init(pipe_data);
	pipe_data->redirections = ft_calloc(pipe_data->counter.redirections + 1,
			sizeof(t_redirections *), TRUE, "get_pipe_dada");
	while (pipe_tokens[++i])
	{
		replaced = handling_quotes(pipe_tokens[i]->token, -1, ' ');
		quotes = s_d_quotes(replaced);
		if (ft_strcmp(pipe_tokens[i]->type, "command") == 0)
		{
			pipe_data->command = quotes;
			pipe_data->argv = ft_realloc(pipe_data->argv, quotes, TRUE);
		}
		else if (ft_strcmp(pipe_tokens[i]->type, "delimiter") == 0)
		{
			pipe_data->delimiter = ft_realloc(pipe_data->delimiter, quotes, TRUE);
			pipe_data->is_herdoc = TRUE;
		}
		else if (ft_strcmp(pipe_tokens[i]->type, "infile") == 0)
			pipe_data->redirections[++j] = get_redirection(quotes, INFILE);
		else if (ft_strcmp(pipe_tokens[i]->type, "outfile") == 0)
			pipe_data->redirections[++j] = get_redirection(quotes, OUTFILE);
		else if (ft_strcmp(pipe_tokens[i]->type, "app_outfile") == 0)
			pipe_data->redirections[++j] = get_redirection(quotes, APPENDFILE);
		else if (ft_strcmp(pipe_tokens[i]->type, "env_var") == 0)
			pipe_data->argv = ft_realloc(pipe_data->argv, s_d_quotes(
						get_env_variables(pipe_tokens[i]->token, FALSE)), TRUE);
		else if (ft_strcmp(pipe_tokens[i]->type, "option") == 0)
			pipe_data->argv = ft_realloc(pipe_data->argv, quotes, TRUE);
		pipe_tokens[i]->token = 0;
	}
}
