#include "../minishell.h"

void	print_error(char *path)
{
	ft_putstr_fd("cd: ", 2);
	ft_putstr_fd(path, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd("\n", 2);
}

void    mcd(char *path)
{
	char    buff[PATH_MAX];
	char	*home_path;
	int		i;

	i = -1;
	if (getcwd(buff, sizeof(buff)) != NULL)
	{
		i = get_var_index("OLDPWD=");
		if (i != -1)
		{
			free(global_data.envp[i]);
			global_data.envp[i] = ft_strjoin("OLDPWD=", buff);
		}
		else
			global_data.envp = ft_realloc(global_data.envp, ft_strjoin("OLDPWD=", buff));
	}
	if (path && ft_strcmp(path, "~"))
	{
    	if (chdir(path) != 0)
			print_error(path);
	}
	else
	{
		home_path = get_var_val("HOME", FALSE);
		if (chdir(home_path) != 0)
			print_error(path);
		free_str(home_path);
	}
	if (getcwd(buff, sizeof(buff)) != NULL)
	{
		i = get_var_index("PWD=");
		if (i != -1)
		{
			free(global_data.envp[i]);
			global_data.envp[i] = ft_strjoin("PWD=", buff);
		}
		else
			global_data.envp = ft_realloc(global_data.envp,ft_strjoin("PWD=", buff));
	}
}
