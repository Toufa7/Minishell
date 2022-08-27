/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_dup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otoufah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 16:40:28 by otoufah           #+#    #+#             */
/*   Updated: 2022/08/23 16:40:29 by otoufah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	env_dup(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	g_global_data.envp = ft_calloc(i + 1, sizeof(char *));
	i = -1;
	while (env[++i])
		g_global_data.envp[i] = ft_strdup(env[i]);
	g_global_data.envp[i] = NULL;
}
