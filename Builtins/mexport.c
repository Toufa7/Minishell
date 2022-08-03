#include "../minishell.h"

char	*get_key(char *str)
{
	char	*key;
	int		i;

	i = 0;
	key = NULL;
	while (str[i] && str[i] != '=' && str[i] != '+')
	{
		if (!(ft_isalpha(str[i]) || (ft_isdigit(str[i]) && i != 0)))
			break;
		i++;
	}
	if (i > 0)
	{
		key = malloc(sizeof(char) * (i + 1));
		ft_strncpy(key, str, i);
	}
	return key;
}

char	*get_val(char *str, bool include_eqs)
{
	char	*val;
	int		i;
	int		j;

	i = 0;
	j = 0;
	val = NULL;
	while(str[i] && str[i] != '=')
		i++;
	if (str[i])
	{
		while (str[i + j])
			j++;
		val = malloc(sizeof(char) * (j + 1));
		if (!include_eqs)
			i++;
		ft_strncpy(val, str + i, j);
	}
	return val;
}

/*
	-1: invalid op
	 0: Create var
	 1: Add to var
*/

int get_op_type(char *str)
{
	int	type;

	type = -1;
	if (!str[0] || (str[0] && str[0] == '='))
		type =  0;
	if (str[0] && str[1] && str[0] == '+' && str[1] == '=')
		type = 1;
	return (type);
}

void	create_final_var(int op_type, char *key, char *new_val)
{
	char	*final_var;
	char	*final_val;
	char	*old_val;
	int		var_index;

	var_index = get_var_index(key);
	if (var_index != -1 && op_type == 1)
	{
		old_val = get_val(key, TRUE);
		final_val = ft_strjoin(old_val, new_val);
		free_str(old_val);
	}
	else
		final_val = new_val;
	if (final_val)
		final_var = ft_strjoin(key, final_val);
	else
		final_var = ft_strdup(key);
	if (var_index != -1)
	{
		free_str(global_data.envp[var_index]);
		global_data.envp[var_index] = final_var;
	}
	else
		global_data.envp = ft_realloc(global_data.envp, final_var);
	if (var_index != -1 && op_type == 1)
		free_str(final_val);
}

void	mexport(char **argv)
{
	char	*key;
	char	*val;
	int		op_type;
	int		i;

	i = -1;
	op_type = -1;
	while (argv[++i])
	{
		key = get_key(argv[i]);
		if (key)
			op_type = get_op_type(argv[i] + ft_strlen(key));
		val = get_val(key, op_type == 0);
		if (!key || op_type == -1)
		{
			ft_putstr_fd("export: '", 2);
			ft_putstr_fd(argv[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			continue;
		}
		create_final_var(op_type, key, val);
	}
	free_str(key);
	free_str(val);
}