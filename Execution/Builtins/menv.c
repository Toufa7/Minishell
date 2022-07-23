#include "../../minishell.h"

void	menv()
{
	int	i;

	i = -1;
	while (genv[++i])
	{
		ft_putstr_fd(genv[i], 1);
		ft_putstr_fd("\n", 1);
	}
}
