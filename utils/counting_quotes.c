#include "../minishell.h"

int	counting_quotes(char *str, char qtype)
{
	int	i;
	int	single_q;
	int	double_q;

	i = -1;
	single_q = 0;
	double_q = 0;
	while (str[++i])
	{
		if (str[i] == doubles_quotes)
			double_q++;
		if (str[i] == sing_quotes)
			single_q++;
	}
	if (qtype == 'S')
		return (single_q);
	if (qtype == 'D')
		return (double_q);
	else
		return (0);
}