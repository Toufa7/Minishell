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

void	input_counter(t_tokens *counter, t_tokens *tokens)
{
	if (ft_strcmp(tokens->type, "red_input") == 0)
		counter->red_in++;
	else if (ft_strcmp(tokens->type, "red_out") == 0)
		counter->red_out++;
	else if (ft_strcmp(tokens->type, "here_doc") == 0)
		counter->here_do++;
	else if (ft_strcmp(tokens->type, "append") == 0)
		counter->app++;
	else if (ft_strcmp(tokens->type, "command") == 0)
		counter->cmd++;
	else if (ft_strcmp(tokens->type, "infile") == 0)
		counter->redirections++;
	else if (ft_strcmp(tokens->type, "outfile") == 0)
		counter->redirections++;
	else if (ft_strcmp(tokens->type, "app_outfile") == 0)
		counter->redirections++;
	else if (ft_strcmp(tokens->type, "delimiter") == 0)
	{
		counter->delimiter++;
		if (counter->delimiter > 16)
		{
			ft_putstr_fd("Mini-0.0: maximum here-document count exceeded", 2);
			global_data.errno_cp = 2;
			exit(2);
		}
	}
	else if (ft_strcmp(tokens->type, "option") == 0)
		counter->option++;
	counter->total = counter->red_in + counter->option + counter->red_out + counter->here_do + counter->app + counter->cmd + counter->redirections + counter->delimiter;
}
