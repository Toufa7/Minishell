#include "minishell.h"

t_tokens *spliting_with_spaces(char *str)
{
    int i = 0;
    t_tokens *tokens;
    char **line = ft_split(str, ' ');
    while (line[i])
        i++;
    tokens = malloc(sizeof(t_tokens) * (i + 1));
    i = 0;
    while (line[i])
    {
        tokens[i].token = line[i];
        i++;
    }
    tokens[i].token = NULL ;
    free(line);
    return (tokens);
}
