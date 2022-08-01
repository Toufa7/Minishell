#include "../minishell.h"

void    mcd(char *path)
{
	char    buff[PATH_MAX];
	int		i;

	i = -1;
	if (getcwd(buff, sizeof(buff)) != NULL)
	{
		i = get_var_index("OLDPWD=", 7);
		if (i != -1)
		{
			free(global_data.envp[i]);
			global_data.envp[i] = ft_strjoin("OLDPWD=", buff);
		}
		else
			global_data.envp = ft_realloc(global_data.envp,ft_strjoin("OLDPWD=", buff));
	}
    if (chdir(path) != 0)
		ft_putstr_fd(strerror(errno), 2);
	if (getcwd(buff, sizeof(buff)) != NULL)
	{
		i = get_var_index("PWD=", 4);
		if (i != -1)
		{
			free(global_data.envp[i]);
			global_data.envp[i] = ft_strjoin("PWD=", buff);
		}
		else
			global_data.envp = ft_realloc(global_data.envp,ft_strjoin("PWD=", buff));
	}
}
