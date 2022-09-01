/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_tokens.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchfa <abouchfa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 22:34:59 by otoufah           #+#    #+#             */
/*   Updated: 2022/08/30 14:55:49 by abouchfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	type_define(t_token *token, char *str, t_bool flag)
{
	token->type = str;
	token->token = get_env_variables(token->token, flag);
}

t_bool	check_cmd_exist(t_token **tokens)
{
	int	i;

	i = -1;
	while (tokens[++i])
		if (ft_strcmp(tokens[i]->type, "command") == 0)
			return (TRUE);
	return (FALSE);
}

void	set_token_type(t_token *token, t_token *pre_toekn, t_token **tokens)
{
	int	f;

	if (ft_strcmp(token->token, "<<") == 0)
		token->type = "here_doc";
	else if (ft_strcmp(token->token, "<") == 0)
		token->type = "red_input";
	else if (ft_strcmp(token->token, ">") == 0)
		token->type = "red_out";
	else if (ft_strcmp(token->token, ">>") == 0)
		token->type = "append";
	else if (pre_toekn && ft_strcmp(pre_toekn->type, "red_input") == 0)
		type_define(token, "infile", TRUE);
	else if (pre_toekn && ft_strcmp(pre_toekn->type, "red_out") == 0)
		type_define(token, "outfile", TRUE);
	else if (pre_toekn && ft_strcmp(pre_toekn->type, "append") == 0)
		type_define(token, "app_outfile", TRUE);
	else if (pre_toekn && ft_strcmp(pre_toekn->type, "here_doc") == 0)
		token->type = "delimiter";
	else if (pre_toekn && check_cmd_exist(tokens))
		type_define(token, "option", FALSE);
	else
	{
		type_define(token, "command", TRUE);
		f = 1;
	}
}

t_token	**set_tokens(char *str)
{
	int				i;
	char			**line;
	t_token			**tokens;
	t_token			*token;
	t_token			*pre_token;

	i = 0;
	line = ft_split(str, ' ');
	while (line[i])
		i++;
	tokens = ft_calloc( (i + 1), sizeof(t_token *), TRUE, "set_tokens");
	i = -1;
	while (line[++i])
	{
		token = alloc(sizeof(t_token), "set_tokens");
		token->token = line[i];
		if (i <= 0)
			pre_token = NULL;
		else
			pre_token = tokens[i - 1];
		set_token_type(token, pre_token, tokens);
		tokens[i] = token;
	}
	tokens[i] = NULL;
	return (tokens);
}
