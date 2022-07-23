#include "../minishell.h"

char	*handling_double_quotes(char *str)
{
	int		i;
	int		j;
	char	*dup;

	dup = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!dup)
		return (NULL);
	i = -1;
	while (str[++i])
	{
		if (str[i] == '"')
		{
			j = i;
			if (str[j] == '"')
				dup[j] = str[j];
			while (str[++j] != '"')
			{
				if (str[j] == ' ')
					dup[j] = '~';
				else
					dup[j] = str[j];
			}
			if (str[j] == '"')
				dup[j] = str[j];
			i = j;
		}
		else
			dup[i] = str[i];
	}
	dup[i] = '\0';
	free(str);
	return (dup);
}

char	*getting_back_original_input(char *str)
{
	int		i;
	int		j;
	char	*dup;

	dup = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!dup)
		return (NULL);
	i = -1;
	while (str[++i])
	{
		if (str[i] == '"')
		{
			j = i;
			if (str[j] == '"')
				dup[j] = str[j];
			while (str[++j] != '"')
			{
				if (str[j] == '~')
					dup[j] = ' ';
				else
					dup[j] = str[j];
			}
			if (str[j] == '"')
				dup[j] = str[j];
			i = j;
		}
		else
			dup[i] = str[i];
	}
	dup[i] = '\0';
	free(str);
	return (dup);
}