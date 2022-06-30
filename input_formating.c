#include "mini.h"

char *input_formating(char *str)
{
    int k = -1;
    char red_input = '<';
    char red_output = '>';
    char pipe = '|';
    char variable = '$';
    int allo = 0;
    while (str[++k])
    {
        if ((str[k] == red_input && str[k + 1] != red_input ) || (str[k] == red_output && str[k + 1] != red_output) || str[k] == pipe || str[k] == variable )
        {
            allo++;
        }
    }
    char *spcs = malloc(sizeof(char) * (ft_strlen(str) + (allo * 2) + 1));
    int i = -1;
    int j = 0;
    while (str[++i])
    {
        if ((str[i] == red_input && str[i + 1] == red_input) || (str[i] == red_output && str[i + 1] == red_output))
        {
            spcs[j++] = ' ';
            spcs[j++] = str[i];
        }
        else if (str[i] == pipe || str[i] == variable)
        {
            spcs[j++] = ' ';
            spcs[j++] = str[i];
            spcs[j++] = ' ';
        }
        else if ((str[i] == red_output && str[i + 1] != red_output) || (str[i] == red_input && str[i + 1] != red_input))
        {
            spcs[j++] = ' ';
            spcs[j++] = str[i];
            spcs[j++] = str[i];
            spcs[j++] = ' ';
        }
        else
            spcs[j++] = str[i];
    }
    spcs[j] = '\0';
    return (spcs);
}

int main()
{
    printf("%s\n",input_formating("<<O|sa$n$ti|O>>"));
}