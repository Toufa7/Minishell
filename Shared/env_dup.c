/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_dup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchfa <abouchfa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 16:40:28 by otoufah           #+#    #+#             */
/*   Updated: 2022/08/28 15:22:29 by abouchfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	env_dup(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	g_data.envp = malloc((i + 1) * sizeof(char *));
	i = -1;
	while (env[++i])
		g_data.envp[i] = ft_strdup(env[i], FALSE);
	g_data.envp[i] = NULL;
}
