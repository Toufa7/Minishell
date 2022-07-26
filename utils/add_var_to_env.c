#include "../minishell.h"

void	add_var_to_env(char *var)
{
	char	**tmp;
	int		i;

	i = 0;
	tmp = genv;
	while (tmp[i])
		i++;
	genv = ft_calloc(i + 2, sizeof(char **));
	i = -1;
	while (tmp[++i])
		genv[i] = ft_strdup(tmp[i]);
	genv[i] = var;
	free_arr(tmp);
}