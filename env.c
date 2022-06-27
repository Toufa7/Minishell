#include "mini.h"

char    *get_env_variables(char **env, char *target)
{
	int		i;

	i = 0;
	while (env[i])
	{
		if (ft_strstr(env[i], target))
			return (env[i] + ft_strlen(target));
		i++;
	}
	return (NULL);
}