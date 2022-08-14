/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_analyse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchfa <abouchfa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 22:52:21 by otoufah           #+#    #+#             */
/*   Updated: 2022/07/26 21:37:40 by abouchfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*is_there(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '$')
			return ("in");
	}
	return ("out");
}

void	input_analyse(t_tokens *tokens)
{
	int		i;
	int		cmd;
	int		j;

	tokens->cmp_red_in = "<";
	tokens->cmp_h_doc = "<<";
	tokens->cmp_red_out = ">";
	tokens->cmp_append = ">>";
	i = -1;
	j = 0;
	cmd = 0;
	while (tokens[++i].token)
	{
		while (tokens[i].token[j] == '"')
			j++;
		if (ft_strcmp(tokens[i].token, tokens->cmp_h_doc) == 0)
		{
			tokens[i].type = "here_doc";
		}
		else if (ft_strcmp(tokens[i].token, tokens->cmp_red_in) == 0)
			tokens[i].type = "red_input";
		else if (ft_strcmp(tokens[i].token, tokens->cmp_red_out) == 0)
			tokens[i].type = "red_out";
		else if (ft_strcmp(tokens[i].token, tokens->cmp_append) == 0)
			tokens[i].type = "append";
		else if (ft_strcmp(is_there(tokens[i].token), "in") == 0)
			tokens[i].type = "env_var";
		else if (i > 0 && (ft_strcmp(tokens[i - 1].type, "red_input") == 0))
			tokens[i].type = "infile";
		else if (i > 0 && (ft_strcmp(tokens[i - 1].type, "red_out") == 0))
			tokens[i].type = "outfile";
		else if (i > 0 && (ft_strcmp(tokens[i - 1].type, "append") == 0))
			tokens[i].type = "app_outfile";
		else if (i > 0 && (ft_strcmp(tokens[i - 1].type, "here_doc") == 0))
			tokens[i].type = "delimiter";
		else if (i > 0 && cmd == 1)
			tokens[i].type = "option";
		else
		{
			cmd = 1;
			tokens[i].type = "command";
		}
	}
}
