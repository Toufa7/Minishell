#include "mini.h"

char    **pipes(char *str)
{
    int i = 0;
    while (str[i] != '\0')
    {
        if (str[i] == '|')
            return (ft_split(str, '|'));
        i++;
    }
    return (&str);
}

// int main(int ac, char **av, char **env)
// {
//     while (True)
//     {
//         int i = 0;
//         char *line = readline(GREEN "Mini-0.0$ " RESET);
//         char **inspection = ft_split(line, ' ');

//         while (inspection[i])
//         {
//             int j = 0;
//             while (inspection[i][j])
//             {
//                 if (inspection[i][j] == '|')
//                 {

//                 }
//                 j++;
//             }
//             i++;
//         }
//     }
// }
