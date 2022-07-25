#include "../../minishell.h"

char	*get_key(char *str)
{
	char	*key;
	int		i;
	int		j;

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
		ft_strncpy(str, key, i);
	}
	return key;
}

char	*get_value(char *str)
{
}

bool valid_op(char *str)
{

}

void	mexport(char **argv)
{
	char	**tmp;
	int		var_index;
	int		i;
	int		j;
	int		k;

	i = -1;
	while (argv[++i])
	{
		j = -1;
		while (argv[i][++j])
		{
			if (!(ft_isalpha(argv[i][j]) || (ft_isdigit(argv[i][j]) && j != 0)))
			{
				ft_putstr_fd("unset: '", 2);
				ft_putstr_fd(argv[i], 2);
				ft_putstr_fd("': not a valid identifier\n", 2);
				break;
			}
		}
		var_index = get_var_index(argv[i], ft_strlen(argv[i]));
		if (!argv[i][j] && var_index != -1)
		{
			j = 0;
			tmp = genv;
			while (genv[j])	
				j++;
			genv = malloc((sizeof(char **) * j));
			j = -1;
			k = 0;
			while (tmp[++j])
			{
				if (var_index != j)
					genv[k++] = ft_strdup(tmp[j]);
			}
			genv[k] = NULL;
		}
	}
}