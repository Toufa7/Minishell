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

t_tokens *spliting_with_spaces(char *str)
{
    int i = -1;
    t_tokens *tokens;
    char **line = ft_split(str, ' ');
    while (line[++i])
        ;
    tokens = malloc(sizeof(t_tokens) * (i + 1));
    i = -1;
    while (line[++i])
        tokens[i].token = line[i];
    tokens[i].token = NULL ;
    free(line);
    return (tokens);
}

int main(int ac, char **av, char **env)
{
	t_parse *parse;

	parse = malloc(sizeof(t_parse));
	while (True)
	{
		parse->line = readline(GREEN "Mini-0.0$ " RESET);
        parse->formated_input = input_formating(parse->line);
        add_history(parse->line);
        parse->splt_pipes = ft_split(parse->formated_input, '|');
		int i = -1;
		while (parse->splt_pipes[++i])
		{
            parse->tokens = spliting_with_spaces(parse->splt_pipes[i]);
            input_analyse(parse->tokens);
            int j = -1;
            while (parse->tokens[++j].token)
                printf("%s ---> %s\n", parse->tokens[j].token, parse->tokens[j].type);
		}
	}
}