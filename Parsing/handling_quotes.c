#include "../minishell.h"

// char    *handling_quotes(char *str)
// {
//     int i = -1;
//     char *dup = malloc(sizeof(char) * ft_strlen(str) + 1);
//     if (!dup)
//         return (NULL);
//     while (str[++i])
//     {
//         if (str[i] == ' ')
//             dup[i] = '%';
//         else
//             dup[i] = str[i];
//     }
//     dup[i] = '\0';
//     return (dup);
// }


char	*replace_spaces_with_x(char *str)
{
	int i = -1;

	char *dup = malloc(sizeof(char) * ft_strlen(str + 1));
	while (str[++i])
	{
		if (str[i] == '"')
		{
            int j = i + 1;
            while (str[j] != '"')
            {
                printf("********\n");
                if (str[j] == ' ')
                    dup[j] = '~';
                else
 			        dup[i] =  str[i];
                j++;
            }
		}
		else
			dup[i] =  str[i];
	}
	dup[i] = '\0';
	return (dup);

}

int main()
{
    printf("%s\n",replace_spaces_with_x(readline("")));
}

Makefile
Parsing/get_env_variables.c
Parsing/input_analyse.c
Parsing/input_counter.c
Parsing/input_formating.c
Parsing/input_types.c
Parsing/spliting_with_spaces.c 
minishell.h