/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchfa <abouchfa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 14:44:31 by otoufah           #+#    #+#             */
/*   Updated: 2022/09/02 17:28:35 by abouchfa         ###   ########.fr       */
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
	parse->pipes = ft_calloc(i + 1, sizeof(t_pipe *), TRUE, "Min");
}



void	minishell(t_parse *parse)
{
	int		i;

	i = -1;
	parse->line_double_quotes = handling_quotes(prevent_tabs(parse->line), '|', -1);
	if (!g_data.parse_error)
	{
		set_parse_data(parse);
		while (parse->splt_pipes[++i])
		{
			parse->pipes[i] = alloc(sizeof(t_pipe), "pipe_data");
			parse->no_splt = handling_quotes(parse->splt_pipes[i], ' ', -1);
			parse->pipes[i]->tokens = input_analyse(parse->no_splt);
			count_tokens(parse->pipes[i]);
			g_data.parse_error = check_parse_errors(parse->pipes[i]);
			if (g_data.parse_error)
				break ;
			fill_tokens(parse->pipes[i]);
			// token_and_type(parse->pipes[i]->tokens);
		}
		if (!g_data.parse_error)
			execution(parse->pipes);
	}
}

int		check(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != TAB)
			return (1);
		i++;
	}
	return (0);
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
		if (check(parse->line) == 0)
			continue ; 
		minishell(parse);
		ft_lstclear(g_data.alloc_list);
		if (parse->line)
			free(parse->line);
	}
}
