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

void	update_oldpwd()
{
	char    buff[PATH_MAX];
	int		i;

	i = get_var_index("OLDPWD=");
	if (getcwd(buff, sizeof(buff)) != NULL)
	{
		if (i != -1)
		{
			free(global_data.envp[i]);
			global_data.envp[i] = ft_strjoin("OLDPWD=", buff);
		}
		else
			global_data.envp = ft_realloc(global_data.envp, ft_strjoin("OLDPWD=", buff));
	}
}

void	update_pwd()
{
	char    buff[PATH_MAX];
	int		i;

	i = get_var_index("PWD=");
	if (getcwd(buff, sizeof(buff)) != NULL)
	{
		if (i != -1)
		{
			free(global_data.envp[i]);
			global_data.envp[i] = ft_strjoin("PWD=", buff);
		}
		else
			global_data.envp = ft_realloc(global_data.envp, ft_strjoin("PWD=", buff));
		free_str(global_data.pwd_copy);
		global_data.pwd_copy = ft_strjoin("PWD=", buff);
	}
	else
		ft_putstr_fd("cd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory\n", 2);
}

void    mcd(char *path)
{
	update_oldpwd();
    if (chdir(path) != 0)
		print_error(path);
	else
	{
		global_data.errno_cp = 0;
		update_pwd();
	}
}
