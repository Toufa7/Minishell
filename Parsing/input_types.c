/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_types.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchfa <abouchfa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 22:36:38 by otoufah           #+#    #+#             */
/*   Updated: 2022/08/01 12:23:14 by abouchfa         ###   ########.fr       */
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
	pipe_data->options = NULL;
	pipe_data->is_herdoc = FALSE;
	pipe_data->in_fd_set = FALSE;
	pipe_data->out_fd_set = FALSE;
}

t_pipe_data	*get_pipe_data(t_parse *parse)
{
	t_pipe_data	*pipe_data;
	int		i;

	pipe_data = malloc(sizeof(t_pipe_data));
	var_init(pipe_data);
	i = 0;
	while (parse->tokens[i].token)
	{
		if (ft_strcmp(parse->tokens[i].type, "command") == 0)
			pipe_data->command = parse->tokens[i].token;
		else if (ft_strcmp(parse->tokens[i].type, "outfile") == 0)
			pipe_data->out_files = ft_realloc(pipe_data->out_files, parse->tokens[i].token);
		else if (ft_strcmp(parse->tokens[i].type, "delimiter") == 0)
		{
			pipe_data->delimiter = ft_realloc(pipe_data->delimiter, parse->tokens[i].token);
			pipe_data->is_herdoc = TRUE;
		}
		else if (ft_strcmp(parse->tokens[i].type, "app_outfile") == 0)
			pipe_data->app_outfile = ft_realloc(pipe_data->app_outfile, parse->tokens[i].token);
		else if (ft_strcmp(parse->tokens[i].type, "env_var") == 0)
			pipe_data->options = ft_realloc(pipe_data->options, get_env_variables(parse->tokens[i].token));
		else if (ft_strcmp(parse->tokens[i].type, "option") == 0)
			pipe_data->options = ft_realloc(pipe_data->options, parse->tokens[i].token);
		i++;
	}
	return pipe_data;
}
