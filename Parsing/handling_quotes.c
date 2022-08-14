#include "../minishell.h"

bool	checking_quotes(char *str)
{
	if (counting_quotes(str, 'D') % 2 != 0)
	{
		ft_putstr_fd("Unclosed Doubles Quotes\n", 2);
		global_data.errno_cp = 1;
		rl_on_new_line();
		rl_replace_line("", 0);

		return (TRUE);
	}
	else if (counting_quotes(str, 'S') % 2 != 0)
	{
		ft_putstr_fd("Unclosed Singles Quotes\n", 2);
		global_data.errno_cp = 1;
		rl_on_new_line();
		rl_replace_line("", 0);
		return (TRUE);
	}
	return (FALSE);
}

char	*handling_quotes(char *str, char replaced, char replace_by)
{
	int		i;
	int		j;
	char	*dup;

	global_data.parse_error = checking_quotes(str);
	dup = NULL;
	if (!global_data.parse_error)
	{
		dup = malloc(sizeof(char) * (ft_strlen(str) + 1));
		if (!dup)
			return (NULL);
		i = -1;
		while (str[++i])
		{
			if (str[i] == doubles_quotes || str[i] == sing_quotes)
			{
				j = i;
				if (str[j] == doubles_quotes || str[j] == sing_quotes)
					dup[j] = str[j];
				j = j + 1;
				while (str[j] != doubles_quotes && str[j] != sing_quotes)
				{
					if (str[j] == replaced)
						dup[j] = replace_by;
					else
						dup[j] = str[j];
					j++;
				}
				if (str[j] == doubles_quotes || str[j] == sing_quotes)
					dup[j] = str[j];
				i = j;
			}
			else
				dup[i] = str[i];
		}
		dup[i] = '\0';
		free_str(str);
	}
	return (dup);
}