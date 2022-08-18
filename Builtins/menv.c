#include "../minishell.h"

void	menv(char **argv, char *prefix, bool is_export)
{
	int	eq;
	int	i;
	int	j;

	i = -1;
	if (argv && *argv)
	{
		ft_putstr_fd("env: ", 2);
		ft_putstr_fd(*argv, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		global_data.errno_cp = 127;
	}
	else
	{
		while (global_data.envp[++i])
		{
			j = -1;
			while (global_data.envp[i][++j])
				if (global_data.envp[i][j] == '=')
					break;
			if (global_data.envp[i][j] != '=' && !is_export)
				continue;
			j = -1;
			eq = 0;
			ft_putstr_fd(prefix, global_data.out_fd);
			while(global_data.envp[i][++j])
			{
				write(1, global_data.envp[i] + j, global_data.out_fd);
				if (global_data.envp[i][j] == '=' && is_export)
				{
					write(1, "\"", global_data.out_fd);
					eq = 1;
				}
			}
			if (is_export && eq)
					write(1, "\"", global_data.out_fd);
			ft_putstr_fd("\n", global_data.out_fd);
		}
	}
}
