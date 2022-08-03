#include "../minishell.h"

void    mpwd(void)
{
    char    buff[PATH_MAX];

    if (getcwd(buff, sizeof(buff)) != NULL)
    {
		ft_putstr_fd(buff, 1);
		ft_putstr_fd("\n", 1);
	}
    else
	{
        ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
	}
}