#include "../../minishell.h"

void	munset(char **argv)
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