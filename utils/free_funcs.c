#include "../minishell.h"

void	free_str(char *str)
{
	if (str)
		free(str);
}

void	free_arr(char **arr)
{
	int	i;

	i = -1;
	while (arr && arr[++i])
		free_str(arr[i]);
	if (arr)
		free(arr);
}