/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchfa <abouchfa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 22:36:38 by otoufah           #+#    #+#             */
/*   Updated: 2022/09/01 03:31:17 by abouchfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	var_init(t_pipe *pipe_data)
{
	pipe_data->redirections = ft_calloc(pipe_data->counter.redirections + 1,
			sizeof(t_redirections *), TRUE, "get_pipe_dada");
	pipe_data->delimiter = NULL;
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

void	conditions(t_pipe *pipe_data, t_token *token,
			char *quotes, int *j)
{
	if (ft_strcmp(token->type, "command") == 0)
	{
		pipe_data->command = quotes;
		pipe_data->argv = ft_realloc(pipe_data->argv, quotes, TRUE);
	}
	else if (ft_strcmp(token->type, "delimiter") == 0)
	{
		pipe_data->delimiter = ft_realloc(pipe_data->delimiter, token->token, TRUE);
		pipe_data->is_herdoc = TRUE;
	}
	else if (ft_strcmp(token->type, "infile") == 0)
		pipe_data->redirections[++(*j)] = get_redirection(token->token, INFILE);
	else if (ft_strcmp(token->type, "outfile") == 0)
		pipe_data->redirections[++(*j)] = get_redirection(token->token, OUTFILE);
	else if (ft_strcmp(token->type, "app_outfile") == 0)
		pipe_data->redirections[++(*j)] = get_redirection(token->token, APPENDFILE);
	else if (ft_strcmp(token->type, "option") == 0)
		pipe_data->argv = ft_realloc(pipe_data->argv, quotes, TRUE);
}

void	fill_tokens(t_pipe *pipe_data)
{
	int		i;
	int		j;
	char	*quotes;
	char	*replaced;
	t_token	**pipe_tokens;

	i = -1;
	j = -1;
	pipe_tokens = pipe_data->tokens;
	var_init(pipe_data);
	while (pipe_tokens[++i])
	{
		replaced = handling_quotes(pipe_tokens[i]->token, -1, ' ');
		quotes = remove_quotes(replaced);
		conditions(pipe_data, pipe_tokens[i], quotes, &j);
	}
}