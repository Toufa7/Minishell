#include "../minishell.h"

void	free_str(void *ptr)
{
	if (ptr)
		free(ptr);
}

void	free_arr(void **arr)
{
	int	i;

	i = -1;
	while (arr && arr[++i])
		free_str(arr[i]);
	free_str(arr);
}