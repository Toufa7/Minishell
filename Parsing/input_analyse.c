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

int	ft_chrcmp(const char s1, const char s2)
{
	if (s1 != s2)
		return (s1 - s2);
	else
		return (0);
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
		else
			tokens[i].type = "None";
		if (i == 0 && ft_strcmp(tokens[0].type, "None") == 0)
			tokens[i].type = "command";
		else if (i == 0)
			continue ;
		else if (ft_strcmp(tokens[i - 1].type, "red_input") == 0)
			tokens[i].type = "infile";
		else if (ft_strcmp(tokens[i - 1].type, "red_out") == 0)
			tokens[i].type = "outfile";
		else if (ft_strcmp(tokens[i - 1].type, "append") == 0)
			tokens[i].type = "app_outfile";
		else if (ft_strcmp(tokens[i - 1].type, "here_doc") == 0)
			tokens[i].type = "delimiter";
		else if (ft_chrcmp(tokens[i].token[j], option[0]) == 0 || ft_strcmp(tokens[i - 1].type, "command"))
			tokens[i].type = "option";
		// else if (ft_strcmp(tokens[i - 1].type, "command") == 0 || ft_strcmp(tokens[i - 1].type, "option") == 0)
		// 	tokens[i].type = "option";
		else if (ft_strcmp(tokens[i].type, "None") == 0)
			tokens[i].type = "command";
	}
}
