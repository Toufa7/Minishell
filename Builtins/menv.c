#include "../minishell.h"

void	menv()
{
	int	i;

	i = -1;
	while (global_data.envp[++i])
	{
		ft_putstr_fd(global_data.envp[i], 1);
		ft_putstr_fd("\n", 1);
	}
}
