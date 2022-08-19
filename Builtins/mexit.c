#include "../minishell.h"

void mexit(char **argv)
{
	bool	isarg_digit;
	int		j;
	int		i;

	isarg_digit = TRUE;
	j = -1;
	i = 0;
	if (!argv[0])
	{
		ft_putstr_fd("exit\n", 1);
		exit(global_data.errno_cp);
	}
	while (argv[i][++j])
	{
		if (!(argv[i][j] >= '0' && argv[i][j] <= '9'))
		{
			isarg_digit = FALSE;
			break;
		}
	}
	while (argv[i])
		i++;
	if (!isarg_digit)
	{
		ft_putstr_fd("exit\nexit: ", 2);
		ft_putstr_fd(argv[0], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		global_data.errno_cp = 255;
		exit(255);
	}
	else if (i > 1)
	{
		ft_putstr_fd("exit\nexit: too many arguments\n", 2);
		global_data.errno_cp = 1;
		return;
	}
	else
	{
		exit(ft_atoi(argv[0]));
		global_data.errno_cp = 0;
	}
}