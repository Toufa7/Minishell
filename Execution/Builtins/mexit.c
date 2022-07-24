#include "../../minishell.h"

void mexit(char **argv)
{
	bool	isarg_digit;
	int		j;
	int		i;

	isarg_digit = TRUE;
	j = -1;
	i = 0;
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
		ft_putstr_fd("exit: ", 2);
		ft_putstr_fd(argv[0], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		exit(255);
	}
	else if (i > 1)
	{
		ft_putstr_fd("exit: too many arguments\n", 2);
		return;
	}
	else
		exit(ft_atoi(argv[0]));
}