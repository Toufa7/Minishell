#include "../minishell.h"

int		counting_quotes(char *str, char specify)
{
	int i = -1;
	int single_q = 0;
	int double_q = 0;
	while (str[++i])
	{
		if (str[i] == 34)
			double_q++;
		if (str[i] == 39)
			single_q++;
	}
	if (specify == 'S')
		return (single_q);
	if (specify == 'D')
		return (double_q);
	else
		return (0);
}

void	checking_quotes(char *str)
{
	if (counting_quotes(str, 'D') % 2 != 0)
	{
		printf("Unclosed Doubles Quotes\n");
		exit(FAILURE);
	}
	if (counting_quotes(str, 'S') % 2 != 0)
	{
		printf("Unclosed Singles Quotes\n");
		exit(FAILURE);
	}
}

char	*handling_quotes(char *str)
{
	int		i;
	int		j;
	char	*dup;
	dup = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!dup)
		return (NULL);
	i = -1;
	checking_quotes(str);
	while (str[++i])
	{
		if (str[i] == 34 || str[i] == 39)
		{
			j = i;
			if (str[j] == 34 || str[j] == 39)
				dup[j] = str[j];
			j = j + 1;
			while (str[j] != 34 && str[j] != 39)
			{
				if (str[j] == ' ')
					dup[j] = '~';
				else
					dup[j] = str[j];
				j++;
			}
			if (str[j] == 34 || str[j] == 39)
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

// int main()
// {
// 	while (1)
// 	{
// 		printf("%s\n",handling_quotes(readline("")));
// 	}
// }