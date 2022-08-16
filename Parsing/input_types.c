/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_types.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchfa <abouchfa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 22:36:38 by otoufah           #+#    #+#             */
/*   Updated: 2022/08/15 11:55:35 by abouchfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	var_init(t_pipe_data *pipe_data)
{
	pipe_data->in_files = NULL;
	pipe_data->out_files = NULL;
	pipe_data->app_outfile = NULL;
	pipe_data->delimiter = NULL;
	pipe_data->command = NULL;
	pipe_data->argv = NULL;
	pipe_data->is_herdoc = FALSE;
	pipe_data->in_fd_set = FALSE;
	pipe_data->out_fd_set = FALSE;
}

t_pipe_data	*get_pipe_data(t_parse *parse)
{
	int			i;
	char		*without_d_quotes;
	char		*without_s_quotes = "";
	char		*replaced;
	t_pipe_data	*pipe_data;

	i = -1;
	pipe_data = malloc(sizeof(t_pipe_data));
	var_init(pipe_data);
	while (parse->tokens[++i].token)
	{
		replaced = handling_quotes(parse->tokens[i].token, -1, ' ');
		without_d_quotes = remove_quotes(replaced, DOUBLES_QUOTES);
		if (ft_strcmp(parse->tokens[i].type, "command") == 0)
		{
			pipe_data->command = without_d_quotes;
			pipe_data->argv = ft_realloc(pipe_data->argv, without_s_quotes);
		}
		else if (ft_strcmp(parse->tokens[i].type, "outfile") == 0)
			pipe_data->out_files = ft_realloc(pipe_data->out_files, without_d_quotes);
		else if (ft_strcmp(parse->tokens[i].type, "delimiter") == 0)
		{
			pipe_data->delimiter = ft_realloc(pipe_data->delimiter, without_d_quotes);
			pipe_data->is_herdoc = TRUE;
		}
		else if (ft_strcmp(parse->tokens[i].type, "infile") == 0)
			pipe_data->in_files = ft_realloc(pipe_data->in_files, without_d_quotes);
		else if (ft_strcmp(parse->tokens[i].type, "app_outfile") == 0)
			pipe_data->app_outfile = ft_realloc(pipe_data->app_outfile, without_d_quotes);
		else if (ft_strcmp(parse->tokens[i].type, "env_var") == 0)
			pipe_data->argv = ft_realloc(pipe_data->argv, remove_quotes(get_env_variables(parse->tokens[i].token), DOUBLES_QUOTES));
		else if (ft_strcmp(parse->tokens[i].type, "option") == 0)
			pipe_data->argv = ft_realloc(pipe_data->argv, without_d_quotes);
		free_str(parse->tokens[i].token);
	}
	return (pipe_data);
}
