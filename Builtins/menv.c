#include "../minishell.h"

void	menv(char **argv, char *prefix)
{
	int	i;

	i = -1;
	if (argv && *argv)
	{
		ft_putstr_fd("env: ", 2);
		ft_putstr_fd(*argv, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
	else
	{
		while (global_data.envp[++i])
		{
			ft_putstr_fd(prefix, 1);
			ft_putstr_fd(global_data.envp[i], 1);
			ft_putstr_fd("\n", 1);
		}
	}
}
