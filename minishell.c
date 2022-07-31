/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchfa <abouchfa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 14:44:31 by otoufah           #+#    #+#             */
/*   Updated: 2022/07/31 14:43:49 by abouchfa         ###   ########.fr       */
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

int main(int ac, char **av, char **env)
{
	(void) ac;
	(void) av;
	t_parse *parse;

	parse = malloc(sizeof(t_parse));
	env_dup(env);
	while (TRUE)
	{
		parse->line = readline(GREEN "Mini-0.0$ " RESET);
		parse->line_double_quotes = handling_quotes(parse->line);
		add_history(parse->line_double_quotes);
		parse->formated_input = input_formating(parse->line_double_quotes);
		parse->splt_pipes = ft_split(parse->formated_input, '|');
		int i = 0;
		while (parse->splt_pipes[i])
			i++;
		parse->pipe_data = ft_calloc(i + 1, sizeof(t_pipe_data *));
		i = -1;
		while (parse->splt_pipes[++i])
		{
			int j = -1;
			parse->tokens = spliting_with_spaces(parse->splt_pipes[i]);
			input_analyse(parse->tokens);
			initializer(parse->tokens);
			while (parse->tokens[++j].token)
			{
				printf("0----- > %s\n", get_env_variables(parse->tokens[j].token));
			}
			parse->pipe_data[i] = get_pipe_data(parse);
		}
		mecho(parse->pipe_data[0]->options);
		// i = -1;
		// while (parse->pipe_data[++i])
		// {
		// 	int j = -1;
		// 	printf("cmd: %s\n", parse->pipe_data[i]->command);
		// 	printf ("delimiters: ");
		// 	while (parse->pipe_data[i]->delimiter[++j])
		// 		printf ("%s ", parse->pipe_data[i]->delimiter[j]);
		// 	printf("\n------------------\n");
		// }
	}
}