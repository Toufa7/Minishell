#include "../minishell.h"

int until_this(char *str, char until)
{
    int i = -1;
    while (str[++i])
    {
        if (str[i] == until)
            break;
    }
    return (i);
}

char    *hello_quotes(char *str)
{
    int     i = 0;
    char    *new = "";
    char    *here;
    while (str[i])
    {
        if (str[i] == doubles_quotes)
        {
            int len = until_this(&str[i + 1], doubles_quotes);
            new = ft_strjoin(new, ft_substr(str + 1, i, len));
            i += len + 1;
        }
        else
        {
            here = ft_substr(&str[i], i, until_this(&str[i], doubles_quotes));
            new = ft_strjoin(new, here);
            i+= ft_strlen(here);
        }
    }
    return (new);
}

// int main()
// {
//     while (1)
//     {
//         char *str = readline("");
//         printf("|%s|\n", hello_quotes(str));
//     }
// }