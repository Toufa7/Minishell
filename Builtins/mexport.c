/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mexport.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchfa <abouchfa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 16:19:59 by otoufah           #+#    #+#             */
/*   Updated: 2022/09/01 06:10:29 by abouchfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_var(int var_index, char *final_val, char *key)
{
	char	*var;
	char	**tmp;

	if (final_val)
		var = ft_strjoin(key, final_val);
	else
		var = key;
	if (var_index != -1)
	{
		free_str(g_data.envp[var_index]);
		g_data.envp[var_index] = ft_strdup(var, FALSE);
	}
	else
	{
		tmp = g_data.envp;
		g_data.envp = ft_realloc(g_data.envp, var, FALSE);
		free_arr((void **) tmp);
	}
	g_data.errno_cp = 0;
}

void	create_final_var(int op_type, char *key, char *new_val, int var_index)
{
	char	*final_val;
	char	*old_val;

	if (var_index != -1 && op_type == 2)
		return ;
	if (var_index != -1 && op_type == 1)
	{
		old_val = get_var_val(var_index);
		final_val = ft_strjoin(old_val, new_val);
		if (!final_val)
			final_val = ft_strdup(old_val, TRUE);
		final_val = ft_strjoin("=", final_val);
	}
	else if (op_type == 2)
		final_val = ft_strdup(new_val, TRUE);
	else
	{
		if (new_val)
			final_val = ft_strjoin("=", new_val);
		else
			final_val = ft_strdup("=", TRUE);
	}
	add_var(var_index, final_val, key);
}

t_bool	check_errors(char *str, char **key, char **val, int *op_type)
{
	*key = get_key(str);
	if (*key)
		*op_type = get_op_type(str + ft_strlen(*key));
	*val = get_val(str);
	if (!*key || *op_type == -1)
	{
		ft_putstr_fd("Mini: export: '", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		g_data.errno_cp = 1;
		return (FALSE);
	}
	return (TRUE);
}

void	mexport(char **argv)
{
	char	*key;
	char	*val;
	int		op_type;
	int		i;

	i = -1;
	key = NULL;
	val = NULL;
	if (!argv || !*argv)
		menv(NULL, "declare -x ", TRUE);
	while (argv && *argv && argv[++i])
	{
		if (argv[i][0] == '-')
		{
			ft_putstr_fd("Mini: export: ", 2);
			ft_putstr_fd(argv[i], 2);
			ft_putstr_fd("invalid option\n", 2);
			g_data.errno_cp = 2;
			break ;
		}
		else if (check_errors(argv[i], &key, &val, &op_type))
			create_final_var(op_type, key, val, get_var_index(key));
	}
}
