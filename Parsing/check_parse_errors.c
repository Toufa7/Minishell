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

bool	err(char *str_1, char *str_2, char *str_3)
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
	char	*tn;
	char	*next_type;
	char	*next_token;
	size_t	i;

	i = 0;
	while (i < parse->tokens->total && parse->tokens[i].token)
	{
		type = parse->tokens[i].type;
		tn = parse->tokens[i].token;
		next_token = parse->tokens[i + 1].token;
		next_type = parse->tokens[i + 1].type;
		if (compare(type, next_type, next_token) == 1)
			return (err("Mini: no delimiter in front of ", tn, "\n"));
		else if (compare(type, next_type, next_token) == 2)
			return (err("Mini: no output file in front of red out ", tn, "\n"));
		else if (compare(type, next_type, next_token) == 3)
			return (err("Mini: no appended file in front of append ", tn, "\n"));
		else if (compare(type, next_type, next_token) == 4)
			return (err("Mini: no input file to be readead from ", tn, "\n"));
		i++;
	}
	return (FALSE);
}
