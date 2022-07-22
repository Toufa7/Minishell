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
<<<<<<< HEAD



/*

echo $$ =  Display PID of shell

echo $? = The shell obtained status of grep (shell built-in)

which 'command' == get command's path
4 8
echo 
echo lol$USER jsdhidcg$PWD
echo lol$USER jsdhidcg'$PWD'
echo lol$USER jsdhidcg"$PWD"
echo lol$USERjsdhidcg$PWD
echo $USER
echo lol$USERjsdhidcg$PWDfu
echo $lol$USERjsdhidcg$PWDfu
echo "$lol$USERjsdhidcg$PWDuy"
echo $lol"$USER"jsdhidcg$PWDuy
echo lol"$USER"jsdhidcg$PWDuy
echo lol"$USER"jsdhidcg"$PWD"uy
echo lol"$USER"jsdhidcg'$PWD'uy
echo lol"$USER"jsdhidcg$PWDuy

*/
=======
>>>>>>> 52df6307705b6b982477149da97c4566d31a4ed1
