/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_analyse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchfa <abouchfa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 22:52:21 by otoufah           #+#    #+#             */
/*   Updated: 2022/08/25 02:03:11 by abouchfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
	Goal of this function
	is to specifying each token his type (delimiter, command, option ...
	cat >> $US
	cd ~/
*/

void	tokens_type_init(t_tokens *tokens)
{
	tokens->cmp_red_in = "<";
	tokens->cmp_h_doc = "<<";
	tokens->cmp_red_out = ">";
	tokens->cmp_append = ">>";
	tokens->set_as_cmd = 0;
}

void	type_define(t_tokens *tokens, char *str, int i, t_bool flag)
{
	tokens[i].type = str;
	tokens[i].token = get_env_variables(tokens[i].token, flag);
}

void	loop_and_assign(t_tokens *tokens, int i)
{
	if (ft_strcmp(tokens[i].token, tokens->cmp_h_doc) == 0)
			tokens[i].type = "here_doc";
	else if (ft_strcmp(tokens[i].token, tokens->cmp_red_in) == 0)
		tokens[i].type = "red_input";
	else if (ft_strcmp(tokens[i].token, tokens->cmp_red_out) == 0)
		tokens[i].type = "red_out";
	else if (ft_strcmp(tokens[i].token, tokens->cmp_append) == 0)
		tokens[i].type = "append";
	else if (i > 0 && (ft_strcmp(tokens[i - 1].type, "red_input") == 0))
		type_define(tokens, "infile", i, TRUE);
	else if (i > 0 && (ft_strcmp(tokens[i - 1].type, "red_out") == 0))
		type_define(tokens, "outfile", i, TRUE);
	else if (i > 0 && (ft_strcmp(tokens[i - 1].type, "append") == 0))
		type_define(tokens, "app_outfile", i, TRUE);
	else if (i > 0 && (ft_strcmp(tokens[i - 1].type, "here_doc") == 0))
		tokens[i].type = "delimiter";
	else if (i > 0 && tokens->set_as_cmd == 1)
		type_define(tokens, "option", i, FALSE);
	else
	{
		tokens->set_as_cmd = 1;
		type_define(tokens, "command", i, TRUE);
	}
}

void	input_analyse(t_tokens *tokens)
{
	int	i;

	i = -1;
	tokens_type_init(tokens);
	while (tokens[++i].token)
	{
		loop_and_assign(tokens, i);
	}
}
