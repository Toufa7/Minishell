#include "../minishell.h"

void	print_error(char *path)
{
	ft_putstr_fd("cd: ", 2);
	ft_putstr_fd(path, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd("\n", 2);
	global_data.errno_cp = errno;
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
			free(global_data.envp[i]);
			global_data.envp[i] = ft_strjoin("OLDPWD=", buff);
		}
		else
			global_data.envp = ft_realloc(global_data.envp, ft_strjoin("OLDPWD=", buff));
	}
	else
		ft_putstr_fd("cd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory\n", 2);
    if (chdir(path) != 0)
		print_error(path);
	else
		global_data.errno_cp = 0;
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
