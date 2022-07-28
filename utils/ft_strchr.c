#include "../minishell.h"

char	*ft_strchr(const char *s, int c)
{
	int				i;
	unsigned char	alpha;
	char			*string;

	string = (char *)s;
	alpha = c;
	i = 0;
	while (string[i] != '\0')
	{
		if (string[i] == alpha)
			return (&string[i + 1]);
		i++;
	}
	if (alpha == 0)
		return (&string[i]);
	return (0);
}