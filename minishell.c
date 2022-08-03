/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchfa <abouchfa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 14:44:31 by otoufah           #+#    #+#             */
/*   Updated: 2022/08/01 16:03:41 by abouchfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*

TODO: ✅❓
	✅ duplicate environment variables
	❓ link parsing part with execuaation
	All tokens are in a double pointer in pipe_data struct parse->pipe_data->x;
	system("leaks Minishell");
*/

#include "minishell.h"

void    looping(char **str)
{
	int i = 0;
	if (!str)
		return ;
	while (str[i])
	{
		printf("%s\n", str[i]);
		i++;
	}
}


void	counting(t_parse *parse)
{
	int j = -1;
	while (parse->tokens[++j].token)
	{
		input_counter(parse->tokens, &parse->tokens[j]);
	}
}

void	control_c(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		// rl_on_new_line();
		// rl_replace_line("", 0);
		// rl_redisplay();
	}
}

void	getting_back(char **str)
{
	int i = -1;
	while (str[++i])
	{
		str[i] = handling_quotes(str[i], -1, ' ');
	}
}

int main(int ac, char **av, char **env)
{
	(void) ac;
	(void) av;
	t_parse *parse;

	parse = malloc(sizeof(t_parse));
	env_dup(env);
	while (TRUE)
	{
		// signal(SIGINT, control_c); // Ctrl+C
		// signal(SIGQUIT, SIG_IGN); // Ctrl + Backslash
		parse->line = readline(GREEN "Mini-0.0$ " RESET);
		if (!parse->line || ft_strcmp(parse->line, "exit") == 0) // Ctrl + D 
			exit(0);
		parse->line_double_quotes = handling_quotes(parse->line, ' ', -1);
		add_history(parse->line_double_quotes);
		parse->formated_input = input_formating(parse->line_double_quotes);
		parse->splt_pipes = ft_split(parse->formated_input, '|');
		getting_back(parse->splt_pipes);
		int i = 0;
		while (parse->splt_pipes[i])
			i++;
		parse->pipe_data = ft_calloc(i + 1, sizeof(t_pipe_data *));
		i = -1;
		while (parse->splt_pipes[++i])
		{
			parse->tokens = spliting_with_spaces(parse->splt_pipes[i]);
			input_analyse(parse->tokens);
			initializer(parse->tokens);
			counting(parse);
			stop_executing(parse);
			parse->pipe_data[i] = get_pipe_data(parse);
		}
		execution(parse->pipe_data);
	}
}