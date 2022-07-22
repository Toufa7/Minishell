/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_types.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otoufah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 22:36:38 by otoufah           #+#    #+#             */
/*   Updated: 2022/07/02 22:36:40 by otoufah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	var_init(t_input *input)
{
	input->in_files = ft_calloc(1, sizeof(char *));
	input->out_files = ft_calloc(1, sizeof(char *));
	input->app_outfile = ft_calloc(1, sizeof(char *));
	input->delimiter = ft_calloc(1, sizeof(char *));
	input->command = ft_calloc(1, sizeof(char *));
}

char	**ft_realloc(char **input, char *str)
{
	int		i;
	char	**new_input;

	i = 0;
	while (input[i])
		i++;
	new_input = calloc(i + 2, sizeof(char *));
	i = 0;
	while (input[i])
	{
		new_input[i] = input[i];
		i++;
	}
	new_input[i] = str;
	free(input);
	return (new_input);
}

void	input_types(t_parse *parse)
{
	int	i;

	parse->input = malloc(sizeof(t_input));
	var_init(parse->input);
	i = 0;
	while (parse->tokens[i].token)
	{
		if (ft_strcmp(parse->tokens[i].type, "outfile") == 0)
			parse->input->out_files = ft_realloc(parse->input->out_files,
					parse->tokens[i].token);
		else if (ft_strcmp(parse->tokens[i].type, "delimiter") == 0)
			parse->input->delimiter = ft_realloc(parse->input->delimiter,
					parse->tokens[i].token);
		else if (ft_strcmp(parse->tokens[i].type, "app_outfile") == 0)
			parse->input->app_outfile = ft_realloc(parse->input->app_outfile,
					parse->tokens[i].token);
		else if (ft_strcmp(parse->tokens[i].type, "command") == 0)
			parse->input->command = ft_realloc(parse->input->command,
					parse->tokens[i].token);
		i++;
	}
}
