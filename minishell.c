/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchfa <abouchfa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 14:44:31 by otoufah           #+#    #+#             */
/*   Updated: 2022/08/30 17:40:31 by abouchfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_g_data(void)
{
	g_data.pre_pipe_infd = -1;
	g_data.size = 0;
	g_data.in_fd = 0;
	g_data.out_fd = 1;
	g_data.pre_pipe_infd = -1;
	g_data.last_child_id = 0;
	g_data.parse_error = FALSE;
	g_data.redirection_error = FALSE;
}

void	init_pipe_counter(t_pipe_data *pipe_data)
{
	pipe_data->counter.app = 0;
	pipe_data->counter.cmd = 0;
	pipe_data->counter.delimiter = 0;
	pipe_data->counter.env_var = 0;
	pipe_data->counter.here_do = 0;
	pipe_data->counter.option = 0;
	pipe_data->counter.red_in = 0;
	pipe_data->counter.red_out = 0;
	pipe_data->counter.redirections = 0;
	pipe_data->counter.total = 0;
}

void	check_nbr_of_delimiters(int delimiters)
{
	if (delimiters > 16)
	{
		ft_putstr_fd("Mini-0.0: maximum here-document count exceeded", 2);
		g_data.errno_cp = 2;
		exit(2);
	}
}

void	count_pipe_tokens(t_pipe_token **pipe_tokens, t_pipe_data *pipe_data)
{
	int	i;

	i = -1;
	init_pipe_counter(pipe_data);
	while (pipe_tokens[++i])
	{
		if (ft_strcmp(pipe_tokens[i]->type, "red_input") == 0)
			pipe_data->counter.red_in++;
		else if (ft_strcmp(pipe_tokens[i]->type, "red_out") == 0)
			pipe_data->counter.red_out++;
		else if (ft_strcmp(pipe_tokens[i]->type, "here_doc") == 0)
			pipe_data->counter.here_do++;
		else if (ft_strcmp(pipe_tokens[i]->type, "append") == 0)
			pipe_data->counter.app++;
		else if (ft_strcmp(pipe_tokens[i]->type, "command") == 0)
			pipe_data->counter.cmd++;
		else if (ft_strcmp(pipe_tokens[i]->type, "infile") == 0)
			pipe_data->counter.redirections++;
		else if (ft_strcmp(pipe_tokens[i]->type, "outfile") == 0)
			pipe_data->counter.redirections++;
		else if (ft_strcmp(pipe_tokens[i]->type, "app_outfile") == 0)
			pipe_data->counter.redirections++;
		else if (ft_strcmp(pipe_tokens[i]->type, "option") == 0)
			pipe_data->counter.option++;
		else if (ft_strcmp(pipe_tokens[i]->type, "delimiter") == 0)
		{
			pipe_data->counter.delimiter++;
			check_nbr_of_delimiters(pipe_data->counter.delimiter);
		}
	}
}

void	getting_back(char **str)
{
	int	i;

	i = -1;
	while (str[++i])
		str[i] = handling_quotes(str[i], -1, '|');
}

void	minishell(t_parse *parse)
{
	int	i;
	t_pipe_token	**pipe_tokens;

	parse->line_double_quotes = handling_quotes(parse->line, '|', -1);
	if (!g_data.parse_error)
	{
		parse->formated_input = input_formating(parse->line_double_quotes);
		parse->splt_pipes = ft_split(parse->formated_input, '|');
		getting_back(parse->splt_pipes);
		i = 0;
		while (parse->splt_pipes[i])
			i++;
		parse->pipes_data = ft_calloc(i + 1, sizeof(t_pipe_data *), TRUE, "Min");
		i = -1;
		while (parse->splt_pipes[++i])
		{
			parse->pipes_data[i] = alloc(sizeof(t_pipe_data), "pipe_data");
			parse->no_splt = handling_quotes(parse->splt_pipes[i], ' ', -1);
			pipe_tokens = set_pipe_tokens(parse->no_splt);
			count_pipe_tokens(pipe_tokens, parse->pipes_data[i]);
			g_data.parse_error = check_parse_errors(pipe_tokens);
			if (g_data.parse_error)
				break ;
			set_pipe_data(parse->pipes_data[i], pipe_tokens);
		}
		execution(parse->pipes_data);
	}
}

int	main(int ac, char **av, char **env)
{
	t_parse	*parse;

	(void) ac;
	(void) av;
	g_data.alloc_list = malloc(sizeof(t_alloc_lst *));
	*(g_data.alloc_list) = NULL;
	parse = malloc(sizeof(t_parse));
	g_data.errno_cp = 0;
	signal(SIGINT, parent_sigint);
	signal(SIGQUIT, SIG_IGN);
	env_dup(env);
	while (TRUE)
	{
		init_g_data();
		parse->line = readline("Mini-0.0$ ");
		if (!parse->line)
			exit(g_data.errno_cp);
		add_history(parse->line);
		minishell(parse);
		ft_lstclear(g_data.alloc_list);
		if (parse->line)
			free(parse->line);
	}
}
