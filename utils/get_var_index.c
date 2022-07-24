#include "../minishell.h"

int	get_var_index(char *var)
{
	int	j;
	int	i;

	j = -1;
	i = -1;
	while (genv[++j])
	{
		if (ft_strncmp(genv[j] , var, 7) == 0)
		{
			i = j;
			break;
		}
	}
	return (i);
}