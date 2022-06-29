#include "mini.h"

void    printf_s(char *str)
{
    printf("--> %s\n",str);
}

void    printf_d(int str)
{
    printf("%d\n",str);
}

char    *variable(char *str)
{
	int i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			return (&str[i + 1]);
		i++;
	}

	return (NULL);
}

char    *get_env_variables(char **env, char *target)
{
	int	i = 0;
    target = ft_strjoin(variable(target), "=");
	while (env[i])
	{
		if (ft_strstr(env[i], target))
		{
        	return (env[i] + ft_strlen(target));
        }
        i++;
	}
	return ("\n");
}