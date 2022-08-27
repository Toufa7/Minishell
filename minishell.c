/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchfa <abouchfa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 14:44:31 by otoufah           #+#    #+#             */
/*   Updated: 2022/08/27 15:59:10 by abouchfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_global_data(void)
{
	g_global_data.pre_pipe_infd = -1;
	g_global_data.size = 0;
	g_global_data.is_in_herdoc = FALSE;
	g_global_data.in_fd = 0;
	g_global_data.out_fd = 1;
	g_global_data.pre_pipe_infd = -1;
	g_global_data.last_child_id = 0;
	g_global_data.parse_error = FALSE;
	g_global_data.redirection_error = FALSE;
}

void	counting(t_parse *parse)
{
	int	j;

	j = -1;
	while (parse->tokens[++j].token)
		input_counter(parse->tokens, &parse->tokens[j]);
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

	parse->line_double_quotes = handling_quotes(parse->line, '|', -1);
	if (!g_global_data.parse_error)
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
			input_analyse(parse->tokens);
			initializer(parse->tokens);
			counting(parse);
			g_global_data.parse_error = check_parse_errors(parse);
			if (g_global_data.parse_error)
				break ;
			parse->pipe_data[i] = get_pipe_data(parse);
		}
		execution(parse->pipe_data);
	}
}

void	ft_lstclear(t_list **lst)
{
	t_list	*temp;

	while (*lst)
	{
		//printf("1 --> %s\n", (*lst)->content);
		temp = (*lst)->next;
		printf("2\n");
		if (*lst && (*lst)->content)
			free((*lst)->content);
		printf("3\n");
		if (*lst)
			free(*lst);
		printf("4\n");
		(*lst) = temp;
		printf("5\n");
	}
}

int	main(int ac, char **av, char **env)
{
	t_parse	*parse;

	(void) ac;
	(void) av;
	g_global_data.alloc_list = malloc(sizeof(t_list *));
	parse = malloc(sizeof(t_parse));
	g_global_data.errno_cp = 0;
	signal(SIGINT, parent_sigint);
	signal(SIGQUIT, SIG_IGN);
	env_dup(env);
	while (TRUE)
	{
		init_global_data();
		parse->line = readline("Mini-0.0$ ");
		if (!parse->line)
			exit(g_global_data.errno_cp);
		add_history(parse->line);
		minishell(parse);
		ft_lstclear(g_global_data.alloc_list);
	}
}
