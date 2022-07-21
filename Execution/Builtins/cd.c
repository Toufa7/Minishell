#include "../../minishell.h"

void    cd(char *path)
{
    if(chdir(path) != 0)
		ft_putstr_fd(strerror(errno), 2);
}