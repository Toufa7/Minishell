/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_counter.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchfa <abouchfa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 22:32:04 by otoufah           #+#    #+#             */
/*   Updated: 2022/08/27 16:04:53 by abouchfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_nbr_of_delimiters(t_tokens *cnt)
{
	if (cnt->delimiter > 16)
	{
		ft_putstr_fd("Mini-0.0: maximum here-document count exceeded", 2);
		g_data.errno_cp = 2;
		exit(2);
	}
}

void	input_counter(t_tokens *tkn)
{
	if (ft_strcmp(tkn->type, "red_input") == 0)
		tkn->red_in++;
	else if (ft_strcmp(tkn->type, "red_out") == 0)
		tkn->red_out++;
	else if (ft_strcmp(tkn->type, "here_doc") == 0)
		tkn->here_do++;
	else if (ft_strcmp(tkn->type, "append") == 0)
		tkn->app++;
	else if (ft_strcmp(tkn->type, "command") == 0)
		tkn->cmd++;
	else if (ft_strcmp(tkn->type, "infile") == 0)
		tkn->redirections++;
	else if (ft_strcmp(tkn->type, "outfile") == 0)
		tkn->redirections++;
	else if (ft_strcmp(tkn->type, "app_outfile") == 0)
		tkn->redirections++;
	else if (ft_strcmp(tkn->type, "option") == 0)
		tkn->option++;
	else if (ft_strcmp(tkn->type, "delimiter") == 0)
	{
		tkn->delimiter++;
		check_nbr_of_delimiters(tkn);
	}
	tkn->total = tkn->red_in + tkn->option + tkn->red_out + tkn->here_do
		+ tkn->app + tkn->cmd + tkn->redirections + tkn->delimiter;
}
