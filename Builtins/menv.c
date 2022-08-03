#include "../minishell.h"

void	menv(char **argv)
{
	int	i;

	i = -1;
	if (argv && argv[0])
	{
		ft_putstr_fd("env: ", 2);
		ft_putstr_fd(argv[0], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
	else
	{
		while (global_data.envp[++i])
		{
			ft_putstr_fd(global_data.envp[i], 1);
			ft_putstr_fd("\n", 1);
		}
	}
}
