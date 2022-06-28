#include "mini.h"

typedef struct s_parse
{
    char    *line;
    char    **inspection;
}   t_parse;


char    *variable(char *str)
{
	int i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			return (&str[i + 1]);
		i++;
	}
	return (NULL);
}

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
					printf("%s\n",getenv(variable(parse->inspection[i])));
				j++;
			}
			i++;
		}
	}
}
