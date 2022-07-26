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
	system("leaks a.out");
*/

#include "minishell.h"

void    looping(char **str)
{
	int i = 0;
	while (str[i])
	{
		printf("%s\n", str[i]);
		i++;
	}
}

char	*is_there(char *str)
{
	int i = -1;
	while (str[++i])
	{
		if (str[i] == '$')
			return ("in");
	}
	return ("out");
}

int main(int ac, char **av, char **env)
{
	(void) ac;
	(void) av;
	t_parse *parse;
	int sig; 

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
			if (ft_strcmp(is_there(parse->splt_pipes[i]),"in") == 0)
			{
				exit(1);
			}
			parse->tokens = spliting_with_spaces(parse->splt_pipes[i]);
			input_analyse(parse->tokens);
			initializer(parse->tokens);
			input_types(parse);
			int x = -1;
			while (parse->tokens[++x].token)
				printf("%s -> type %s\n",parse->tokens[x].token, parse->tokens[x].type);
		}
		parse->input->size = i;
	}
}