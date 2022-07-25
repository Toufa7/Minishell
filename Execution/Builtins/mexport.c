#include "../../minishell.h"

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
		key = malloc(sizeof(char *) * (i + 1));
		ft_strncpy(key, str, i);
	}
	return key;
}

char	*get_val(char *str)
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
		val = malloc(sizeof(char *) * (j + 1));
		ft_strncpy(val, str + i + 1, j);
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

void	mexport(char **argv)
{
	char	*key;
	char	*val;
	int		op_type;
	int		var_index;
	int		i;
	// int		j;
	// int		k;

	i = -1;
	op_type = -1;
	while (argv[++i])
	{
		key = get_key(argv[i]);
		val = get_val(argv[i]);
		if (key)
			op_type =  get_op_type(argv[i] + ft_strlen(key));
		// printf("key: %s\n", key);
		// printf("val: %s\n", val);
		// printf("opt: %i\n", op_type);
		// printf("----------------------\n");
		if (!key || op_type == -1)
		{
			ft_putstr_fd("export: '", 2);
			ft_putstr_fd(argv[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			continue;
		}
		var_index = get_var_index(key, ft_strlen(key));
		// j = -1;
		// while (argv[i][++j])
		// {
		// 	if (!(ft_isalpha(argv[i][j]) || (ft_isdigit(argv[i][j]) && j != 0)))
		// 	{
		// 		ft_putstr_fd("unset: '", 2);
		// 		ft_putstr_fd(argv[i], 2);
		// 		ft_putstr_fd("': not a valid identifier\n", 2);
		// 		break;
		// 	}
		// }
		// var_index = get_var_index(argv[i], ft_strlen(argv[i]));
		// if (!argv[i][j] && var_index != -1)
		// {
		// 	j = 0;
		// 	tmp = genv;
		// 	while (genv[j])	
		// 		j++;
		// 	genv = malloc((sizeof(char **) * j));
		// 	j = -1;
		// 	k = 0;
		// 	while (tmp[++j])
		// 	{
		// 		if (var_index != j)
		// 			genv[k++] = ft_strdup(tmp[j]);
		// 	}
		// 	genv[k] = NULL;
		// }
	}
}