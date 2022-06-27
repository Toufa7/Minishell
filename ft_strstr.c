#include "mini.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	size_t		a;
	size_t		b;
	char		*hay;

	hay = (char *)haystack;
	if (needle[0] == 0)
		return (hay);
	a = 0;
	while (hay[a])
	{
		b = 0;
		while (hay[a + b] == needle[b])
		{
			if (needle[b + 1] == 0)
				return (&hay[a]);
			b++;
		}
		a++;
	}
	return (NULL);
}