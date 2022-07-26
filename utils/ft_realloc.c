#include "../minishell.h"

void	ft_realloc(char **input, char *str)
{
	int		i;
	char	**tmp;

	i = 0;
	tmp = input;
	while (tmp[i])
		i++;
	input = ft_calloc(i + 2, sizeof(char **));
	i = -1;
	while (tmp[++i])
		input[i] = tmp[i];
	input[i] = str;
	free_arr(tmp);
}
