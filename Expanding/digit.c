#include "../minishell.h"

char	*ft_digit(char *target, t_bool flag)
{
    int     i;
    char    *output;
    char    *variable;

    i = 0;
    if (target[i + 1] == '0')
	{
		output = ft_strjoin(output, "Minishell");
		i += ft_strlen(until_dollar(&target[i])) + 1;
	}
	else
	{
		variable = until_dollar(&target[i + 2]);
		output = ft_strjoin(output, variable);
		i += ft_strlen(variable) + 2;
	}
    return (output);
}