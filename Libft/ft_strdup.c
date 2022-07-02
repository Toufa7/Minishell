#include "libft.h"
// Creating a new string (dup) that is identical to a string s1.

char	*ft_strdup(const char *s1)
{
	char	*dup;
	size_t	i;
	size_t	l;
	size_t	memory;

	l = ft_strlen(s1);
	memory = (sizeof(char) * l + 1); // allocating new memory for the duplicate string
	dup = (char *)malloc(memory);
	if (!(dup && s1))
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		dup[i] = s1[i]; // copying s1 as it is and past it on the dup and return it 
		i++;
	}
	dup[i] = '\0';
	return (dup);
}