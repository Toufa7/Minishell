/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_types.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchfa <abouchfa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 22:36:38 by otoufah           #+#    #+#             */
/*   Updated: 2022/07/26 21:37:46 by abouchfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void var_init(t_input *input)
{
	input->in_files = NULL;
	input->out_files = NULL;
	input->app_outfile = NULL;
	input->delimiter = NULL;
	input->command = NULL;
	input->options = NULL;
	input->env_var = NULL;
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
			parse->input->out_files = ft_realloc(parse->input->out_files, parse->tokens[i].token);
		else if (ft_strcmp(parse->tokens[i].type, "delimiter") == 0)
			parse->input->delimiter = ft_realloc(parse->input->delimiter, parse->tokens[i].token);
		else if (ft_strcmp(parse->tokens[i].type, "app_outfile") == 0)
			parse->input->app_outfile = ft_realloc(parse->input->app_outfile, parse->tokens[i].token);
		else if (ft_strcmp(parse->tokens[i].type, "command") == 0)
			parse->input->command = ft_realloc(parse->input->command, parse->tokens[i].token);
		else if (ft_strcmp(parse->tokens[i].type, "option") == 0)
			parse->input->options = ft_realloc(parse->input->options, parse->tokens[i].token);
		else if (ft_strcmp(parse->tokens[i].type, "env_var") == 0)
			parse->input->env_var = ft_realloc(parse->input->env_var, parse->tokens[i].token);
		i++;
	}
}
