/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_pipe_tokens.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchfa <abouchfa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 22:34:59 by otoufah           #+#    #+#             */
/*   Updated: 2022/08/30 14:55:49 by abouchfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	type_define(t_pipe_token *toekn, char *str, t_bool flag)
{
	toekn->type = str;
	toekn->token = get_env_variables(toekn->token, flag);
}

void	set_token_type(t_pipe_token *token, t_pipe_token *pre_toekn)
{
	if (ft_strcmp(token->token,  "<<") == 0)
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
	else if (pre_toekn && pre_toekn->set_as_cmd == 1)
		type_define(token, "option", FALSE);
	else
	{
		token->set_as_cmd = 1;
		type_define(token, "command", TRUE);
	}
}

t_pipe_token	**set_pipe_tokens(char *str)
{
	int				i;
	char			**line;
	t_pipe_token	**pipe_tokens;
	t_pipe_token	*token;
	t_pipe_token	*pre_token;

	i = 0;
	line = ft_split(str, ' ');
	while (line[i])
		i++;
	pipe_tokens = alloc(sizeof(t_pipe_token *) * (i + 1), "set_pipe_tokens");
	i = -1;
	while (line[++i])
	{
		token = alloc(sizeof(t_pipe_token), "set_pipe_tokens");
		token->token = line[i];
		if (i <= 0)
			pre_token = NULL;
		else
			pre_token = pipe_tokens[i - 1];
		set_token_type(token, pre_token);
		pipe_tokens[i] = token;
	}
	pipe_tokens[i] = NULL;
	return (pipe_tokens);
}
