/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchfa <abouchfa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 16:41:30 by otoufah           #+#    #+#             */
/*   Updated: 2022/09/02 21:01:53 by abouchfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	parent_sigint(int sig)
{
	(void) sig;
	printf("\n");
	rl_on_new_line();
	// rl_replace_line("", 0);
	rl_redisplay();
	g_data.errno_cp = 1;
}

void	herdoc_sigint(int sig)
{
	(void) sig;
	exit(1);
}

void	void_sig(int sig)
{
	(void) sig;
}
