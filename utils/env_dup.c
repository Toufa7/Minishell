#include "../minishell.h"

void	env_dup(char **env)
{
	int	i;

	i = 0;

	while (env[i])
		i++;
	global_data.envp = ft_calloc(i + 1, sizeof(char *));
	i = -1;
	while (env[++i])
	{
		global_data.envp[i] = ft_strdup(env[i]);
		if (!ft_strncmp(env[i], "PWD=", 5))
			global_data.pwd_copy = ft_strdup(env[i]);
	}
	global_data.envp[i] = NULL;
}