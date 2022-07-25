#include "../minishell.h"

/*
	this function return the index of a var from genv (our global environment variables)
	return -1 if the var don't exist
*/

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