#include "../minishell.h"

void    mpwd(void)
{
    char    buff[PATH_MAX];

    if (getcwd(buff, sizeof(buff)) != NULL)
    {
		ft_putstr_fd(buff, global_data.out_fd);
		ft_putstr_fd("\n", global_data.out_fd);
		global_data.errno_cp = 0;
	}
    else
	{
        ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
		global_data.errno_cp = errno;
	}
}