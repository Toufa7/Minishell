#include "../minishell.h"

/*
	this function return the index of a key from global_data.envp (our global environment variables)
	return -1 if the key don't exist
*/

int	get_var_index(char *key)
{
	int	j;
	int	i;

	j = -1;
	i = -1;
	while (global_data.envp[++j])
	{
		if (ft_strncmp(global_data.envp[j] , key, ft_strlen(key)) == 0)
		{
			i = j;
			break;
		}
	}
	return (i);
}