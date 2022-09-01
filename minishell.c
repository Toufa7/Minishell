/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchfa <abouchfa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 14:44:31 by otoufah           #+#    #+#             */
/*   Updated: 2022/09/01 21:40:05 by abouchfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	getting_back(char **str)
{
	int	i;

	i = -1;
	while (str[++i])
		str[i] = handling_quotes(str[i], -1, '|');
}

void	set_parse_data(t_parse *parse)
{
	int	i;

	i = 0;
	parse->formated_input = input_formating(parse->line_double_quotes);
	parse->splt_pipes = ft_split(parse->formated_input, '|');
	getting_back(parse->splt_pipes);
	while (parse->splt_pipes[i])
		i++;
	parse->pipes_data = ft_calloc(i + 1, sizeof(t_pipe_data *), TRUE, "Min");
}

void	minishell(t_parse *parse)
{
	int		i;

	i = -1;
	parse->line_double_quotes = handling_quotes(parse->line, '|', -1);
	if (!g_data.parse_error)
	{
		set_parse_data(parse);
		while (parse->splt_pipes[++i])
		{
			parse->pipes_data[i] = alloc(sizeof(t_pipe_data), "pipe_data");
			parse->no_splt = handling_quotes(parse->splt_pipes[i], ' ', -1);
			parse->pipes_data[i]->tokens = set_pipe_tokens(parse->no_splt);
			count_pipe_tokens(parse->pipes_data[i]);
			g_data.parse_error = check_parse_errors(
					parse->pipes_data[i]->tokens);
			if (g_data.parse_error)
				break ;
			set_pipe_data(parse->pipes_data[i]);
			//token_and_type(parse->pipes_data[i]->tokens, parse->pipes_data[i]);
		}
		if (!g_data.parse_error)
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
