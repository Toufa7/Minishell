#include "mini.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen(src);
	if (!dstsize)
		return (len);
	while (src[i] && (i < dstsize - 1))
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (len);
}


static int	count_words(const char *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		if ((i == 0 && s[i] != c) || (s[i - 1] == c && s[i] != c))
			count++;
		i++;
	}
	return (count);
}

static char	**spliting(char **arr, char const *s, char c)
{
	int		i;
	int		j;
	int		len;

	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		len = i;
		while (s[len] && s[len] != c)
			len++;
		if (s[i])
		{
			arr[j] = malloc((len - i + 1) * sizeof(char));
			ft_strlcpy(arr[j++], s + i, len - i + 1);
		}
		i = len;
	}
	arr[j] = 0;
	return (arr);
}

char	**ft_split(char const *s, char c)
{
	char	**arr;

	if (!s)
		return (NULL);
	arr = malloc((count_words(s, c) + 1) * sizeof(char *));
	if (!arr)
		return (NULL);
	spliting(arr, s, c);
	return (arr);
}