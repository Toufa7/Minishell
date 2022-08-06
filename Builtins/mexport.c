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
	 2: Just a var name
*/

int get_op_type(char *str)
{
	int	type;

	type = -1;
	if (!str || !str[0])
		type = 2;
	if (str[0] && str[0] == '=')
		type =  0;
	if (str[0] && str[1] && str[0] == '+' && str[1] == '=')
		type = 1;
	return (type);
}

void	create_final_var(int op_type, char *key, char *new_val)
{
	printf("key: %s | opt: %i | val: %s\n", key, op_type,new_val);
	char	*final_var;
	char	*final_val;
	char	*old_val;
	int		var_index;

	old_val = get_var_val(key, TRUE);
	var_index = get_var_index(key);
	if (var_index != -1 && (op_type == 1 || op_type == 2))
	{
		printf("old_v: %s\n", old_val);
		final_val = ft_strjoin(old_val, new_val);
		if (!final_val)
			final_val = ft_strdup(old_val);
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

bool	check_errors(char *str, char *key, char *val, int *op_type)
{
	if (counting_quotes(str, 'D') % 2 != 0)
	{
		ft_putstr_fd("Unclosed Doubles Quotes\n", 2);
		return FALSE;
	}
	else if (counting_quotes(str, 'S') % 2 != 0)
	{
		ft_putstr_fd("Unclosed Singles Quotes\n", 2);
		return FALSE;
	}
	key = get_key(str);
	if (key)
		*op_type = get_op_type(str + ft_strlen(key));
	val = get_val(str, *op_type == 0);
	if (!key || *op_type == -1)
	{
		ft_putstr_fd("export: '", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		return FALSE;
	}
	return TRUE;
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
		menv(NULL, "declare -x ");
		return ;
	}
	while (argv[++i])
	{
		if (check_errors(argv[i], key, val, &op_type))
			create_final_var(op_type, key, val);
	}
	free_str(key);
	free_str(val);
}