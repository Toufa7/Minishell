/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_types.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchfa <abouchfa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 22:36:38 by otoufah           #+#    #+#             */
/*   Updated: 2022/07/26 17:55:13 by abouchfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void var_init(t_input *input)
{
	input->in_files = ft_calloc(1, sizeof(char *));
	input->out_files = ft_calloc(1, sizeof(char *));
	input->app_outfile = ft_calloc(1, sizeof(char *));
	input->delimiter = ft_calloc(1, sizeof(char *));
	input->command = ft_calloc(1, sizeof(char *));
	input->options = ft_calloc(1, sizeof(char *));
}

void input_types(t_parse *parse)
{
	int i;

	parse->input = malloc(sizeof(t_input));
	var_init(parse->input);
	i = 0;
	while (parse->tokens[i].token)
	{
		if (ft_strcmp(parse->tokens[i].type, "outfile") == 0)
			ft_realloc(parse->input->out_files, parse->tokens[i].token);
		else if (ft_strcmp(parse->tokens[i].type, "delimiter") == 0)
			ft_realloc(parse->input->delimiter, parse->tokens[i].token);
		else if (ft_strcmp(parse->tokens[i].type, "app_outfile") == 0)
			ft_realloc(parse->input->app_outfile, parse->tokens[i].token);
		else if (ft_strcmp(parse->tokens[i].type, "command") == 0)
			ft_realloc(parse->input->command, parse->tokens[i].token);
		else if (ft_strcmp(parse->tokens[i].type, "option") == 0)
			ft_realloc(parse->input->options, parse->tokens[i].token);
		i++;
	}
}
