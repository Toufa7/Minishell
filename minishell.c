/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchfa <abouchfa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 14:44:31 by otoufah           #+#    #+#             */
/*   Updated: 2022/07/21 10:41:12 by abouchfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int main()
{
	t_parse *parse;

	parse = malloc(sizeof(t_parse));
	while (TRUE)
	{
		parse->line = readline(GREEN "Mini-0.0$ " RESET);
		add_history(parse->line);
		parse->formated_input = input_formating(parse->line);
		parse->splt_pipes = ft_split(parse->formated_input, '|');
		int i = -1;
		while (parse->splt_pipes[++i])
		{
			printf("Pipeline -> %d\n", i + 1);
			parse->tokens = spliting_with_spaces(parse->splt_pipes[i]);
			input_analyse(parse->tokens);
			initializer(parse->tokens);
			input_types(parse);
			int x = -1;
			while (parse->tokens[++x].token)
			{
				printf("%s -> type %s\n",parse->tokens[x].token,parse->tokens[x].type);
			}
			printf("----out--- \n");
			looping(parse->input->out_files);
		}
	}
}