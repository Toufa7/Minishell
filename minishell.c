/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchfa <abouchfa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 14:44:31 by otoufah           #+#    #+#             */
/*   Updated: 2022/08/27 09:42:14 by abouchfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_glbl_data(void)
{
	g_glbl_data.pre_pipe_infd = -1;
	g_glbl_data.size = 0;
	g_glbl_data.is_in_herdoc = FALSE;
	g_glbl_data.in_fd = 0;
	g_glbl_data.out_fd = 1;
	g_glbl_data.pre_pipe_infd = -1;
	g_glbl_data.last_child_id = 0;
	g_glbl_data.parse_error = FALSE;
	g_glbl_data.redirection_error = FALSE;
}

void	getting_back(char **str)
{
	int	i;

	i = -1;
	while (str[++i])
		str[i] = handling_quotes(str[i], -1, '|');
}

void	analyse_init_count(t_parse *parse)
{
	int	j;

	j = -1;
	input_analyse(parse->tokens);
	token_counter_init(parse->tokens);
	while (parse->tokens[++j].token)
		input_counter(parse->tokens, &parse->tokens[j]);
}

void	minishell(t_parse *parse)
{
	int	i;

	parse->line_double_quotes = handling_quotes(parse->line, '|', -1);
	if (!g_glbl_data.parse_error)
	{
		parse->formated_input = input_formating(parse->line_double_quotes);
		parse->splt_pipes = ft_split(parse->formated_input, '|');
		getting_back(parse->splt_pipes);
		i = 0;
		while (parse->splt_pipes[i])
			i++;
		parse->pipe_data = ft_calloc(i + 1, sizeof(t_pipe_data *));
		i = -1;
		while (parse->splt_pipes[++i])
		{
			parse->no_splt = handling_quotes(parse->splt_pipes[i], ' ', -1);
			parse->tokens = spliting_with_spaces(parse->no_splt);
			analyse_init_count(parse);
			token_and_type(parse);
			g_glbl_data.parse_error = check_parse_errors(parse);
			if (g_glbl_data.parse_error == 1)
				break ;
			parse->pipe_data[i] = get_pipe_data(parse);
		}
		execution(parse->pipe_data);
	}
}

int	main(int ac, char **av, char **env)
{
	t_parse	*parse;

	(void) ac;
	(void) av;
	parse = malloc(sizeof(t_parse));
	g_glbl_data.errno_cp = 0;
	signal(SIGINT, parent_sigint);
	signal(SIGQUIT, SIG_IGN);
	env_dup(env);
	while (TRUE)
	{
		init_glbl_data();
		parse->line = readline("Mini-0.0$ ");
		if (!parse->line)
			exit(g_glbl_data.errno_cp);
		add_history(parse->line);
		minishell(parse);
	}
}
