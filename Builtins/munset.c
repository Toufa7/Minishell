/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   munset.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchfa <abouchfa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 16:20:07 by otoufah           #+#    #+#             */
/*   Updated: 2022/09/01 05:32:08 by abouchfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	remove_var(char *var)
{
	char	**tmp;
	int		var_index;
	int		j;
	int		k;

	var_index = get_var_index(var);
	if (var_index != -1)
	{
		j = 0;
		tmp = g_data.envp;
		while (g_data.envp[j])
			j++;
		g_data.envp = malloc((sizeof(char *) * j));
		j = -1;
		k = 0;
		while (tmp[++j])
		{
			if (var_index != j)
				g_data.envp[k++] = ft_strdup(tmp[j], FALSE);
		}
		g_data.envp[k] = NULL;
		free_arr((void **) tmp);
	}
}

void	munset(char **argv)
{
	int		i;
	int		j;

	i = -1;
	while (argv[++i])
	{
		g_data.errno_cp = 0;
		j = validate_var_name(argv[i]);
		if (argv[i][j] || j == 0)
		{
			ft_putstr_fd("Mini: unset: '", 2);
			ft_putstr_fd(argv[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			g_data.errno_cp = 1;
		}
		else
			remove_var(argv[i]);
	}
}
