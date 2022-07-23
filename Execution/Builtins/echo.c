#include "../../minishell.h"

void    echo(char **argv)
{
	bool new_line;
	bool valid_arg;
	int	i;
	int	j;

	j = -1;
	new_line = false;
	valid_arg = true;
	while(argv[++j] && argv[j][0] == '-' && valid_arg)
	{
		i = 0;
		while(argv[j][++i])
		{
			if(argv[j][i] != 'n')
			{
				valid_arg = false;
				break;
			}
			else if (argv[j][i + 1] == '\0')
				new_line = true;
		}
	}
	j--;
	while(argv[j])
	{
		ft_putstr_fd(argv[j++], 1);
		if (argv[j])
			ft_putstr_fd(" ", 1);
	}
	if (!new_line)
		ft_putstr_fd("\n", 1);
}


