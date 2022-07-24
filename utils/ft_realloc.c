#include "../minishell.h"

char	**ft_realloc(char **input, char *str)
{
	int		i;
	char	**new_input;

	i = 0;
	while (input[i])
		i++;
	new_input = calloc(i + 2, sizeof(char *));
	i = 0;
	while (input[i])
	{
		new_input[i] = input[i];
		i++;
	}
	new_input[i] = str;
	free(input);
	return (new_input);
}
