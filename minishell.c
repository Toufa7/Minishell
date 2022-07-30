/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchfa <abouchfa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 14:44:31 by otoufah           #+#    #+#             */
/*   Updated: 2022/07/26 21:42:59 by abouchfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*

TODO: ✅❓
	✅ duplicate environment variables
	❓ link parsing part with execuaation
	All tokens are in a double pointer in input struct parse->input->x;
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
		int i = -1;
		while (parse->splt_pipes[++i])
		{
			printf("Pipes -> %d\n",i + 1);
			parse->tokens = spliting_with_spaces(parse->splt_pipes[i]);
			input_analyse(parse->tokens);
			initializer(parse->tokens);
			input_types(parse);
			printf("\n	Delimiters Are	\n");
			looping(parse->input->delimiter);
			// for (int j = -1;parse->tokens[++j].token;)
			// {
			// 	printf("%s	->	Type	->	%s\n",parse->tokens[j].token, parse->tokens[j].type);
			// }
			for (int j = 0; parse->tokens[j].token;j++)
			{
				input_counter(parse->tokens, &parse->tokens[j]);
			}
			printf("	Nbr of Delimiter %zu\n",parse->tokens->delimiter);
		}
	}
}