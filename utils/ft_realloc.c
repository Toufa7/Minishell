#include "../minishell.h"

char	**ft_realloc(char **pipe_data, char *str)
{
	char	**tmp;
	char	**new_input;
	int		i;

	i = 0;
	tmp = pipe_data;
	while (tmp && tmp[i])
		i++;
	new_input = ft_calloc(i + 2, sizeof(char *));
	i = -1;
	while (tmp && tmp[++i])
		new_input[i] = ft_strdup(tmp[i]);
	if (!tmp)
		i++;
	new_input[i++] = ft_strdup(str);
	new_input[i] = NULL;
	free_arr(tmp);
	return (new_input);
}
