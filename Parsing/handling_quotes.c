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


void    just_replace(char *str, char *dup, char alpha)
{
    int i = -1;
    while (str[++i] != '"')
    {
        if (str[i] == alpha)
            dup[i] = '~';
        else
            dup[i] = str[i];
    }
}

char	*replace_spaces_with_x(char *str)
{
	int i = -1;
	char *dup = malloc(sizeof(char) * ft_strlen(str + 1));
    if (!dup)
        return (NULL);
	while (str[++i])
	{
		if (str[i] == '"')
		{
            int j = i;
            while (str[++j] != '"')
            {
                just_replace(str, dup, ' ');
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
    while (1)
    {
        printf("%s\n",replace_spaces_with_x(readline("")));
    }
}