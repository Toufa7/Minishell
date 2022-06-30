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

char **spliting_with_pipes(char *str)
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

char    **spliting_with_spaces(char *str)
{
    int i = 0;
    char space = ' ';
    while (str[i])
    {
        if (str[i] == space)
        {
            return (ft_split(str, space));
        }
        i++;
    }
    return (NULL);
}

char    *input_analyse(char *str)
{
    int i = -1;
    while (str[++i])
    {
        if (str[0] == '<' && str[1] == '<')
            return ("here_doc");
        if (str[0] == '>' && str[1] == '>')
            return ("append");
        if (str[0] == '>')
            return ("red_output");
        if (str[0] == '<')
            return ("red_input");
    }
    return ("arg");
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
        parse->splt_pipes = spliting_with_pipes(parse->line);
		int i = -1;
		while (parse->splt_pipes[++i])
		{
            parse->splt_spaces = spliting_with_spaces(parse->splt_pipes[i]);
            int j = -1;
            while (parse->splt_spaces[++j])
            {
                int o = -1;
                if (input_analyse(parse->splt_spaces[j] == "arg"))
                {
                    int k = -1;
                    while (parse->only_args[++k])
                    {
                        parse->only_args[k] = parse->splt_spaces[j];
                    }
                }
            }
		}
	}
}