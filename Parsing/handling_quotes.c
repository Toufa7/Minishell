#include "../minishell.h"

char	*replace_spaces_with_x(char *str)
{
	int i;
    int j;
    char *dup;

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
                {
                    printf("Copy at %d\n",j);
                    dup[j] = '~';
                }
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
    return (dup);
}


// int main()
// {
//     while (1)
//     {
//         printf("%s\n",replace_spaces_with_x(readline("")));
//     }
// }