#include "../minishell.h"

int	get_var_index(char *var, int n)
{
	int	j;
	int	i;

	j = -1;
	i = -1;
	while (genv[++j])
	{
		if (ft_strncmp(genv[j] , var, n) == 0)
		{
			i = j;
			break;
		}
	}
	return (i);
}