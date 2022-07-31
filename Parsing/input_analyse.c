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
	int i = -1;
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
	char	*red_input;
	char	*here_doc;
	char	*red_out;
	char	*append;
	char	*option;

	red_input = "<";
	here_doc = "<<";
	red_out = ">";
	append = ">>";
	option = "-";
	i = -1;
	int cmd = 0;
	int j = 0;
	while (tokens[++i].token)
	{
		while (tokens[i].token[j] == '"')
			j++;
		if (ft_strcmp(tokens[i].token, red_input) == 0)
			tokens[i].type = "red_input";
		else if (ft_strcmp(tokens[i].token, red_out) == 0)
			tokens[i].type = "red_out";
		else if (ft_strcmp(is_there(tokens[i].token), "in") == 0)
			tokens[i].type = "env_var";
		else if (ft_strcmp(tokens[i].token, here_doc) == 0)
			tokens[i].type = "here_doc";
		else if (ft_strcmp(tokens[i].token, append) == 0)
			tokens[i].type = "append";
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