#include "../minishell.h"

void	ft_close(int n, int s)
{
	(void) s;
	if (n > 2)
		close(n);
}