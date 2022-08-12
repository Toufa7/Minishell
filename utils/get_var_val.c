#include "../minishell.h"

char	*get_var_val(int var_index, bool include_eqs)
{
	char	*val;
	char	*var;
	int		i;
	int		j;

	i = 0;
	j = 0;
	val = NULL;
	var = global_data.envp[var_index];
	while(var[i] && var[i] != '=')
		i++;
	if (var[i])
	{
		while (var[i + j])
			j++;
		val = malloc(sizeof(char) * (j + 1));
		if (!include_eqs)
			i++;
		ft_strncpy(val, var + i, j);
	}
	return val;
}