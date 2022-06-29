#include "mini.h"

int space_index(char *str)
{
    int i;

    i = 0;
    while (str[i] == ' ')
        i++;
    return (i);
}

char    *skip_spaces(char *str)
{
    int i;
    int j;
    char *after_spaces = malloc(sizeof(char) + ft_strlen(str) + 1);

    j = 0;
    i = space_index(str);
    while (str[i])
    {
        after_spaces[j] = str[i];
        j++;
        i++;
    }
	after_spaces[j] = '\0';
    return (after_spaces);
}

char **pipes(char *str)
{
    int i = 0;
    char pipe = '|';
    while (str[i])
    {
        if (str[i] == pipe)
        {
            return (ft_split(str, pipe));
        }
        i++;
    }
    return (NULL);
}

