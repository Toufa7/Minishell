/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mexport.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchfa <abouchfa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 16:19:59 by otoufah           #+#    #+#             */
/*   Updated: 2022/08/30 22:54:20 by abouchfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_key(char *str)
{
	char	*key;
	int		i;

	i = 0;
	key = NULL;
	while (str[i] && str[i] != '=' && str[i] != '+')
	{
		if (!(ft_isalpha(str[i]) || str[i] == BACKSLASH || (ft_isdigit(str[i]) && i != 0) || str[i] == '_'))
			break ;
		i++;
	}
	if (i > 0)
	{
		key = alloc(sizeof(char) * (i + 1), "export val");
		ft_strncpy(key, str, i);
	}
	return (key);
}

char	*get_val(char *str)
{
	char	*val;
	int		i;
	int		j;

	i = 0;
	j = 0;
	val = NULL;
	while (str[i] && str[i] != '=')
		i++;
	if (str[i])
	{
		while (str[i + j])
			j++;
		val = alloc(sizeof(char) * (j + 1), "export val");
		ft_strncpy(val, str + i + 1, j);
	}
	return (val);
}

/*
	-1: invalid op
	 0: Create var
	 1: Add to var
	 2: Just a var name
*/

int	get_op_type(char *str)
{
	int	type;

	type = -1;
	if (!str || !str[0])
		type = 2;
	if (str[0] && str[0] == '=' && str[1] != '=')
		type = 0;
	if (str[0] && str[1] && str[0] == '+' && str[1] == '=')
		type = 1;
	return (type);
}

void	create_final_var(int op_type, char *key, char *new_val)
{
	char	*final_var;
	char	*cmpined_val;
	char	*old_val;
	int		var_index;

	var_index = get_var_index(key);
	if (var_index != -1 && op_type == 2)
		return ;
	if (var_index != -1 && op_type == 1)
	{
		old_val = get_var_val(var_index);
		cmpined_val = ft_strjoin(old_val, new_val);
		if (!cmpined_val)
			cmpined_val = ft_strdup(old_val, TRUE);
		cmpined_val = ft_strjoin("=", cmpined_val);
	}
	else if (op_type == 2)
		cmpined_val = ft_strdup(new_val, TRUE);
	else
	{
		if (new_val)
			cmpined_val = ft_strjoin("=", new_val);
		else
			cmpined_val = ft_strdup("=", TRUE);
	}
	if (cmpined_val)
		final_var = ft_strjoin(key, cmpined_val);
	else
		final_var = ft_strjoin(key, "");
	if (var_index != -1)
	{
		free_str(g_data.envp[var_index]);
		g_data.envp[var_index] = ft_strdup(final_var, FALSE);
	}
	else
		g_data.envp = ft_realloc(g_data.envp, final_var, FALSE);
	g_data.errno_cp = 0;
}

t_bool	check_errors(char *str, char **key, char **val, int *op_type)
{
	*key = get_key(str);
	if (*key)
		*op_type = get_op_type(str + ft_strlen(*key));
	*val = get_val(str);
	if (!*key || *op_type == -1)
	{
		ft_putstr_fd("export: '", 2);
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
	op_type = -1;
	key = NULL;
	val = NULL;
	if (!argv || !*argv)
	{
		menv(NULL, "declare -x ", TRUE);
		return ;
	}
	while (argv[++i])
	{
		if (argv[i][0] == '-')
		{
			ft_putstr_fd("export: ", 2);
			ft_putstr_fd(argv[i], 2);
			ft_putstr_fd(": invalid option\n", 2);
			g_data.errno_cp = 2;
			break;
		}
		else if (check_errors(argv[i], &key, &val, &op_type))
			create_final_var(op_type, key, val);
	}
}
