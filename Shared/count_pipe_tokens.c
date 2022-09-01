/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_tokens.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchfa <abouchfa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 03:03:08 by abouchfa          #+#    #+#             */
/*   Updated: 2022/09/01 03:03:22 by abouchfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_herdoc_limit(int delimiters)
{
	if (delimiters > 16)
	{
		ft_putstr_fd("Mini: maximum here-document count exceeded", 2);
		g_data.errno_cp = 2;
		exit(2);
	}
}

void	count_helper(t_pipe *pipe_data, t_token *token)
{
	if (ft_strcmp(token->type, "red_input") == 0)
		pipe_data->counter.red_in++;
	else if (ft_strcmp(token->type, "red_out") == 0)
		pipe_data->counter.red_out++;
	else if (ft_strcmp(token->type, "here_doc") == 0)
		pipe_data->counter.here_do++;
	else if (ft_strcmp(token->type, "append") == 0)
		pipe_data->counter.app++;
	else if (ft_strcmp(token->type, "command") == 0)
		pipe_data->counter.cmd++;
	else if (ft_strcmp(token->type, "infile") == 0)
		pipe_data->counter.redirections++;
	else if (ft_strcmp(token->type, "outfile") == 0)
		pipe_data->counter.redirections++;
	else if (ft_strcmp(token->type, "app_outfile") == 0)
		pipe_data->counter.redirections++;
	else if (ft_strcmp(token->type, "option") == 0)
		pipe_data->counter.option++;
	else if (ft_strcmp(token->type, "delimiter") == 0)
	{
		pipe_data->counter.delimiter++;
		check_herdoc_limit(pipe_data->counter.delimiter);
	}
}

void	total_tokens(t_pipe *pipe_data)
{
	pipe_data->counter.total = pipe_data->counter.red_in
		+ pipe_data->counter.red_out + pipe_data->counter.here_do
		+ pipe_data->counter.app + pipe_data->counter.cmd
		+ pipe_data->counter.redirections + pipe_data->counter.option
		+ pipe_data->counter.delimiter;
}

void	count_tokens(t_pipe *pipe_data)
{
	int	i;

	i = -1;
	init_pipe_counter(pipe_data);
	while (pipe_data->tokens[++i])
		count_helper(pipe_data, pipe_data->tokens[i]);
	total_tokens(pipe_data);
}
