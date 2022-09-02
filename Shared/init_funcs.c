/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_funcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchfa <abouchfa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 02:35:31 by abouchfa          #+#    #+#             */
/*   Updated: 2022/09/02 16:48:55 by abouchfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_g_data(void)
{
	g_data.pre_pipe_infd = -1;
	g_data.size = 0;
	g_data.out_fd = 1;
	g_data.pre_pipe_infd = -1;
	g_data.last_child_id = 0;
	g_data.parse_error = FALSE;
	g_data.redirection_error = FALSE;
}

void	init_pipe_counter(t_pipe *pipe_data)
{
	pipe_data->counter.app = 0;
	pipe_data->counter.cmd = 0;
	pipe_data->counter.delimiter = 0;
	pipe_data->counter.here_do = 0;
	pipe_data->counter.option = 0;
	pipe_data->counter.red_in = 0;
	pipe_data->counter.red_out = 0;
	pipe_data->counter.redirections = 0;
	pipe_data->counter.total = 0;
}
