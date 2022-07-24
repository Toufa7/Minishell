#include "../../minishell.h"

int	get_var_index(char *var)
{
	int	j;
	int	i;

	j = -1;
	i = -1;
	while (genv[++j])
	{
		if (ft_strncmp(genv[j] , var, 7) == 0)
		{
			i = j;
			break;
		}
	}
	return (i);
}

void    mcd(char *path)
{
	char    buff[PATH_MAX];
	int		i;

	i = -1;
	if (getcwd(buff, sizeof(buff)) != NULL)
	{
		i = get_var_index("OLDPWD=");
		if (i != -1)
		{
			free(genv[i]);
			genv[i] = ft_strjoin("OLDPWD=", buff);
		}
		else
			genv = ft_realloc(genv, ft_strjoin("OLDPWD=", buff));
	}
    if (chdir(path) != 0)
		ft_putstr_fd(strerror(errno), 2);
	if (getcwd(buff, sizeof(buff)) != NULL)
	{
		i = get_var_index("PWD=");
		if (i != -1)
		{
			free(genv[i]);
			genv[i] = ft_strjoin("PWD=", buff);
		}
		else
			genv = ft_realloc(genv, ft_strjoin("PWD=", buff));
	}
}
