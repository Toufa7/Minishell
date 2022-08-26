/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_parse_errors.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otoufah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 16:26:08 by otoufah           #+#    #+#             */
/*   Updated: 2022/08/26 16:42:12 by otoufah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	err_exiting(char *str_1, char *str_2, char *str_3)
{
	ft_putstr_fd(str_1, 2);
	ft_putstr_fd(str_2, 2);
	ft_putstr_fd(str_3, 2);
	global_data.errno_cp = 258;
	return (TRUE);
}

int	compare(char	*t, char	*nxt_t, char	*nxt_tok)
{
	if ((ft_strcmp(t, "here_doc") == 0 && !nxt_tok)
		|| (ft_strcmp(t, "here_doc") == 0
			&& (ft_strcmp(nxt_t, "delimiter") != 0)))
		return (1);
	else if ((ft_strcmp(t, "red_out") == 0 && !nxt_tok)
		|| (ft_strcmp(t, "red_out") == 0
			&& (ft_strcmp(nxt_t, "outfile") != 0)))
		return (2);
	else if ((ft_strcmp(t, "append") == 0 && !nxt_tok)
		|| (ft_strcmp(t, "append") == 0
			&& (ft_strcmp(nxt_t, "app_outfile") != 0)))
		return (3);
	else if ((ft_strcmp(t, "red_input") == 0 && !nxt_tok)
		|| ((ft_strcmp(t, "red_input") == 0)
			&& (ft_strcmp(nxt_t, "infile") != 0)))
		return (4);
	else
		return (-1);
}

bool	check_parse_errors(t_parse	*parse)
{
	char	*type;
	char	*tkn;
	char	*next_type;
	char	*next_token;
	size_t	i;

	i = 0;
	if (!parse->tokens[i].token)
		err_exiting("Error", NULL, "\n");
	while (i < parse->tokens->total && parse->tokens[i].token)
	{
		type = parse->tokens[i].type;
		tkn = parse->tokens[i].token;
		next_token = parse->tokens[i + 1].token;
		next_type = parse->tokens[i + 1].type;
		if (compare(type, next_type, next_token) == 1)
			err_exiting("Mini: no delimiter in front of ", tkn, "\n");
		else if (compare(type, next_type, next_token) == 2)
			err_exiting("Mini: no output file in front of red out ", tkn, "\n");
		else if (compare(type, next_type, next_token) == 3)
			err_exiting("Mini: no appended file in front of a append ", tkn, "\n");
		else if (compare(type, next_type, next_token) == 4)
			err_exiting("Mini: no input file to be readead from ", tkn, "\n");
		i++;
	}
	return (FALSE);
}

/*
	- echo hello > "${NotExist}" ==> bash: : No such file or directory 
	- echo hello > ${NotExist}  ==> bash: ${NONEXISTENT}: ambiguous redirect
	- echo hello > "${Exist}" ==> simply creat the file with expanded name
	- echo hello > ${Exist}  ==> the same
	- echo hello > ${Exist but it's a directory}  ==> bash: /Users/otoufah/Desktop/Here_we_go: Is a directory
	if there's nothing in piplines
	if there's no delimiter
	if there's no output file in red out
	if there's no appended file to be redirected 
	if there's no input file to be readead from 
*/
