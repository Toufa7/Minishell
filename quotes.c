#include "minishell.h"

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

char    *single_quotes(char *str)
{
    int     i = 0;
    char    *new = ft_strdup("");
    char    *here;
    while (str[i])
    {
        if (str[i] == sing_quotes)
        {
            int len = until_this(&str[i + 1], sing_quotes);
            new = ft_strjoin(new, ft_substr(str + 1, i, len));
            printf("--> %d\n", len);
            i += len;
        }
        else
        {
            here = ft_substr(&str[i], i, until_this(&str[i], sing_quotes));
            new = ft_strjoin(new, here);
            i+= ft_strlen(here);
        }
    }
    return (new);
}

int main()
{
    while (1)
    {
        char *str = readline("");
        printf("%s\n", single_quotes(str));
    }

}