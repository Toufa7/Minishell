#include "../../minishell.h"

void    cd(char *path)
{
	char    buff[PATH_MAX];
	int		i;

	i = -1;
	if (getcwd(buff, sizeof(buff)) != NULL)
		while (genv[++i])
		{
			if (ft_strncmp(genv[i], "OLDPWD=", 7) == 0)
			{
				free(genv[i]);
				genv[i] = ft_strjoin("OLDPWD=", buff);
			}
		}
    if (chdir(path) != 0)
		ft_putstr_fd(strerror(errno), 2);
	i = -1;
	if (getcwd(buff, sizeof(buff)) != NULL)
		while (genv[++i])
		{
			if (ft_strncmp(genv[i], "PWD=", 4) == 0)
			{
				free(genv[i]);
				genv[i] = ft_strjoin("PWD=", buff);
			}
		}
}
