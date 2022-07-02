#include "minishell.h"

int main(int ac, char **av, char **env)
{
	t_parse *parse;

	parse = malloc(sizeof(t_parse));
	int o = 0;
    while (o < 2)
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
            {
                printf("%s\n",parse->tokens[j].token);
                input_counter(parse->tokens);
            }
		}
	}
}