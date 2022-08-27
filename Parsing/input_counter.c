/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_counter.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchfa <abouchfa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 22:32:04 by otoufah           #+#    #+#             */
/*   Updated: 2022/08/21 01:31:27 by abouchfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	initializer(t_tokens	*tokens)
{
	tokens->red_in = 0;
	tokens->red_out = 0;
	tokens->here_do = 0;
	tokens->app = 0;
	tokens->redirections = 0;
	tokens->delimiter = 0;
	tokens->cmd = 0;
	tokens->total = 0;
	tokens->option = 0;
}

void	check_nbr_of_delimiters(t_tokens *cnt)
{
	if (cnt->delimiter > 16)
	{
		ft_putstr_fd("Mini-0.0: maximum here-document count exceeded", 2);
		g_glbl_data.errno_cp = 2;
		exit(2);
	}
}

void	input_counter(t_tokens *cnt, t_tokens *tokens)
{
	if (ft_strcmp(tokens->type, "red_input") == 0)
		cnt->red_in++;
	else if (ft_strcmp(tokens->type, "red_out") == 0)
		cnt->red_out++;
	else if (ft_strcmp(tokens->type, "here_doc") == 0)
		cnt->here_do++;
	else if (ft_strcmp(tokens->type, "append") == 0)
		cnt->app++;
	else if (ft_strcmp(tokens->type, "command") == 0)
		cnt->cmd++;
	else if (ft_strcmp(tokens->type, "infile") == 0)
		cnt->redirections++;
	else if (ft_strcmp(tokens->type, "outfile") == 0)
		cnt->redirections++;
	else if (ft_strcmp(tokens->type, "app_outfile") == 0)
		cnt->redirections++;
	else if (ft_strcmp(tokens->type, "option") == 0)
		cnt->option++;
	else if (ft_strcmp(tokens->type, "delimiter") == 0)
	{
		cnt->delimiter++;
		check_nbr_of_delimiters(cnt);
	}
	cnt->total = cnt->red_in + cnt->option + cnt->red_out + cnt->here_do
		+ cnt->app + cnt->cmd + cnt->redirections + cnt->delimiter;
}
