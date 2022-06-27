#include "mini.h"

char    *get_env_variables(char **env, char *target)
{
	int	i = 0;
	while (env[i])
	{
		if (ft_strstr(env[i], target))
			return (env[i] + ft_strlen(target) + 1);
		i++;
	}
	return (NULL);
}

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
// char env_variable = '$';

char **input_analyse(char *str)
{
    int i = 0;
    char pipe = '|';
    char quote = '"';
    while (str[i])
    {
        if (str[i] == '"')
        {
            int j = i;
            while (str[j])
            {
                printf("I'm Here");
                if (str[j] == '|')
                    str[j] = '9';
                j++; 
            }
        }
        if (str[i] == pipe)
        {
            return (ft_split(str, pipe));
        }
        i++;
    }
    return (NULL);
}

int main(void)
{
    while (True)
    {
        int     i;
        char    *line;
        char    **analyse;

        i = 0;
        line = readline(GREEN "Mini-0.0$ " RESET);
        add_history(line);
        analyse = input_analyse(line);
        while (analyse[i])
        {
            printf(RESET "%s\n", skip_spaces(analyse[i]));
            i++;
        }
    }
}
