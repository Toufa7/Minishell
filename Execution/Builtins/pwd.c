#include "../../minishell.h"

void    pwd(void)
{
    char    buff[PATH_MAX];

    if (getcwd(buff, sizeof(buff)) != NULL)
        ft_putstr_fd(buff, 1);
    else
        ft_putstr_fd(strerror(errno), 2);
}