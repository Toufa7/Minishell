#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	i;
	size_t	l;
	size_t	memory;

	if (!s)
		return (NULL);
	memory = (sizeof(char) * len + 1);
	sub = (char *)malloc(memory);
	if (!sub)
		return (NULL);
	i = 0;
	l = 0;
	while (s[i] != '\0')
	{
		if (i >= start && l < len)
		{
			sub[l] = s[i];
			l++;
		}
		i++;
	}
	sub[l] = '\0';
	return (sub);
}