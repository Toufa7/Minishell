#include "minishell.h"

char    *input_formating(char *str)
{
    int k;
    int allo;
    char *spcs;

    k = -1;
    allo = 0;
    while (str[++k])
    {
        if ((str[k] == '<' && str[k + 1] != '<' ) || (str[k] == '>' && str[k + 1] != '>') || str[k] == '|' || str[k] == '$')
            allo++;
    }
    spcs = malloc(sizeof(char) * (ft_strlen(str) + (allo * 2) + 1));
    if (!spcs)
        return (NULL);
    int i;
    int j;
    i = -1;
    j = 0;
    while (str[++i])
    {
        if ((str[i] == '<' && str[i + 1] == '<') || (str[i] == '>' && str[i + 1] == '>'))
        {
            spcs[j++] = ' ';
            spcs[j++] = str[i];
            spcs[j++] = str[i];
            i++;
        }
        else if ((str[i] == '>' && str[i + 1] != '>') || (str[i] == '<' && str[i + 1] != '<') || str[i] == '|' || str[i] == '$' )
        {
            spcs[j++] = ' ';
            spcs[j++] = str[i];
            spcs[j++] = ' ';
        }
        else
            spcs[j++] = str[i];
    }
    spcs[j] = '\0';
    return (spcs);
}