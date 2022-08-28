/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   munset.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchfa <abouchfa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 16:20:07 by otoufah           #+#    #+#             */
/*   Updated: 2022/08/27 16:05:31 by abouchfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	munset(char **argv)
{
	char	**tmp;
	int		var_index;
	int		i;
	int		j;
	int		k;

	i = -1;
	tmp = NULL;
	while (argv[++i])
	{
		g_data.errno_cp = 0;
		j = validate_var_name(argv[i]);
		if (argv[i][j])
		{
			ft_putstr_fd("unset: '", 2);
			ft_putstr_fd(argv[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			g_data.errno_cp = 1;
			continue ;
		}
		var_index = get_var_index(argv[i]);
		if (!argv[i][j] && var_index != -1)
		{
			j = 0;
			tmp = g_data.envp;
			while (g_data.envp[j])
				j++;
			g_data.envp = alloc((sizeof(char *) * j));
			j = -1;
			k = 0;
			while (tmp[++j])
			{
				if (var_index != j)
					g_data.envp[k++] = ft_strdup(tmp[j]);
			}
			g_data.envp[k] = NULL;
		}
	}
	//free_arr((void **) tmp);
}
