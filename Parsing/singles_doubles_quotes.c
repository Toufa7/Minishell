#include "../minishell.h"

int	until_this(char *str, char c)
{
	int	i;

	if (!str)
		return (0);
	i = -1;
	while (str[++i])
	{
		if (str[i] == c)
			break ;
	}
	return (i);
}

char	*singles_doubles_quotes(char *str)
{
	int		i;
	int		j;
	int		len;

	if (!str)
		return (NULL);
	i = -1;
	while (str[++i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			len = until_this(&str[i + 1], str[i]);
            if (str[len + i + 1] == '\0')
            {
                printf("Error");
                exit(0);
            }
            str[i] = -1;
            str[len + i + 1] = -1;
			i += len;
		}
	}
    i = -1;
    j = 0;
    while (str[++i])
    {
        if (str[i] == -1)
            continue;
        str[j] = str[i];
        j++;
    }
    str[j] = '\0';
	return (str);
}