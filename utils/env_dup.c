#include "../minishell.h"

/*
FIXME:
	fix this function always use adddress sanitizer
*/

void	env_dup(char **env)
{
	int	i;

	i = 0;

	while (env[i])
		i++;
	genv = malloc((sizeof(char **) * i) + 1);
	i = -1;
	while (env[++i])
		genv[i] = ft_strdup(env[i]);
	genv[i] = NULL;
}