/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pipe_data.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchfa <abouchfa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 22:36:38 by otoufah           #+#    #+#             */
/*   Updated: 2022/08/21 04:37:40 by abouchfa         ###   ########.fr       */
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
	new_redrcs = malloc(sizeof(t_redirections));
	new_redrcs->path = ft_strdup(path); 
	new_redrcs->type = type;
	return new_redrcs;
}

t_pipe_data	*get_pipe_data(t_parse *parse)
{
	int			i;
	int			j;
	char		*without_d_quotes;
	char		*without_s_quotes = "";
	char		*replaced;
	t_pipe_data	*pipe_data;

	i = -1;
	j = -1;
	pipe_data = malloc(sizeof(t_pipe_data));
	var_init(pipe_data);
	pipe_data->redirections = ft_calloc(parse->tokens->redirections + 1, sizeof(t_redirections *));
	while (parse->tokens[++i].token && parse->tokens[i].token)
	{
		replaced = handling_quotes(parse->tokens[i].token, -1, ' ');
		without_d_quotes = singles_doubles_quotes(replaced);
		if (ft_strcmp(parse->tokens[i].type, "command") == 0)
		{
			pipe_data->command = without_d_quotes;
			pipe_data->argv = ft_realloc(pipe_data->argv, without_s_quotes);
		}
		else if (ft_strcmp(parse->tokens[i].type, "delimiter") == 0)
		{
			pipe_data->delimiter = ft_realloc(pipe_data->delimiter, without_d_quotes);
			pipe_data->is_herdoc = TRUE;
		}
		else if (ft_strcmp(parse->tokens[i].type, "infile") == 0)
			pipe_data->redirections[++j] = get_redirection(without_d_quotes, INFILE);
		else if (ft_strcmp(parse->tokens[i].type, "outfile") == 0)
			pipe_data->redirections[++j] = get_redirection(without_d_quotes, OUTFILE);
		else if (ft_strcmp(parse->tokens[i].type, "app_outfile") == 0)
			pipe_data->redirections[++j] = get_redirection(without_d_quotes, APPENDFILE);
		else if (ft_strcmp(parse->tokens[i].type, "env_var") == 0)
		{
			pipe_data->argv = ft_realloc(pipe_data->argv, singles_doubles_quotes(get_env_variables(parse->tokens[i].token)));

		}
		else if (ft_strcmp(parse->tokens[i].type, "option") == 0)
			pipe_data->argv = ft_realloc(pipe_data->argv, without_d_quotes);
		free_str(parse->tokens[i].token);
	}
	return (pipe_data);
}