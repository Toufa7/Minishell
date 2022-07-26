#include "../minishell.h"

void	env_dup(char **env)
{
	int	i;

	i = 0;

	while (env[i])
		i++;
	genv = ft_calloc(i + 1, sizeof(char **));
	i = -1;
	while (env[++i])
		genv[i] = ft_strdup(env[i]);
}