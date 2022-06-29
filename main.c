#include "mini.h"

int main(int ac, char **av, char **env)
{
	t_parse *parse;

	parse = malloc(sizeof(t_parse));
	while (True)
	{
		parse->line = readline(GREEN "Mini-0.0$ " RESET);
		parse->inspection = ft_split(parse->line, ' ');
		int i = 0;
		while (parse->inspection[i])
		{
			int j = 0;
			while (parse->inspection[i][j])
			{
				if (parse->inspection[i][j] == '$')
					printf("%s\t",get_env_variables(env, parse->inspection[i]));
				if (parse->inspection[i][j] == '|')
					printf("%s\t",pipes(parse->inspection[i]));
				j++;
			}
			i++;
		}
		printf("\n");
	}
}

// $USER     $HOME       $TERM     $XPC_FLAGS
// cmd_1 |			cmd_2 	| "omar 	|  toufah"
