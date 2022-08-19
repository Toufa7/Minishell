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
		global_data.errno_cp = 0;
		j = validate_var_name(argv[i]);
		if (argv[i][j])
		{
			ft_putstr_fd("unset: '", 2);
			ft_putstr_fd(argv[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			global_data.errno_cp = 1;
			continue;
		}
		var_index = get_var_index(argv[i]);
		if (!argv[i][j] && var_index != -1)
		{
			j = 0;
			tmp = global_data.envp;
			while (global_data.envp[j])	
				j++;
			global_data.envp = malloc((sizeof(char *) * j));
			j = -1;
			k = 0;
			while (tmp[++j])
			{
				if (var_index != j)
					global_data.envp[k++] = ft_strdup(tmp[j]);
			}
			global_data.envp[k] = NULL;
		}
	}
	free_arr(tmp);
}