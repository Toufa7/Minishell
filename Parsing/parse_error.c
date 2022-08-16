#include "../minishell.h"

bool    parse_error(t_parse *parse)
{
    size_t i = 0;
    if (!parse->tokens[i].token)
    {
        printf("Error\n");
        return TRUE;
    }
    while (i < parse->tokens->total && parse->tokens[i].token)
    {
        printf("Token -> %s\n",parse->tokens[i].token);
        if ((ft_strcmp(parse->tokens[i].type, "here_doc") == 0 && !parse->tokens[i + 1].token) || (ft_strcmp(parse->tokens[i].type, "here_doc") == 0 && (ft_strcmp(parse->tokens[i + 1].type, "delimiter") != 0)))
        {
            printf("Mini: There's no delimiter in front of [%s]\n",parse->tokens[i].token);
            return (TRUE);
        }
        else if ((ft_strcmp(parse->tokens[i].type,"red_out") == 0 && !parse->tokens[i + 1].token) || (ft_strcmp(parse->tokens[i].type, "red_out") == 0 && (ft_strcmp(parse->tokens[i + 1].type, "outfile") != 0)))
        {
            printf("Mini: There's no output file in front of red out [%s]\n",parse->tokens[i].token);
            return (TRUE);
        }
        else if ((ft_strcmp(parse->tokens[i].type, "append") == 0 && !parse->tokens[i + 1].token) || (ft_strcmp(parse->tokens[i].type, "append") == 0 && (ft_strcmp(parse->tokens[i + 1].type, "app_outfile") != 0)))
        {
            printf("Mini: There's no appended file in front of a append [%s]\n", parse->tokens[i].token);
            return (TRUE);
        }
        else if ((ft_strcmp(parse->tokens[i].type, "red_input") == 0 && !parse->tokens[i + 1].token) || ((ft_strcmp(parse->tokens[i].type, "red_input") == 0) && (ft_strcmp(parse->tokens[i + 1].type, "infile") != 0)))
        {
            printf("Mini: There's no input file to be readead from [%s]\n", parse->tokens[i].token);
            return (TRUE);            
        }
        i++;
    }
	return FALSE;
}







// bool    parse_error(t_parse *parse)
// {
//     int i = 0;
//     // if there's nothing in piplines
//     if (!parse->tokens[i].token)
//     {
//             printf("Walo\n");
//             return TRUE;
//     }
//     while ((size_t)i < parse->tokens->total && parse->tokens[i].token)
//     {
//         // if there's no delimiter
//         if ((ft_strcmp(parse->tokens[i].type, "here_doc") == 0 && !parse->tokens[i + 1].token) || (ft_strcmp(parse->tokens[i].type, "here_doc") == 0 && (ft_strcmp(parse->tokens[i + 1].type, "delimiter") != 0)))
//         {
//             printf("Mini: There's no delimiter in front of [%s]\n",parse->tokens[i].token);
//             return (TRUE);
//         }
//         // if there's no output file in red out
//         else if ((ft_strcmp(parse->tokens[i].type,"red_out") == 0 && !parse->tokens[i + 1].token) || (ft_strcmp(parse->tokens[i].type, "red_out") == 0 && (ft_strcmp(parse->tokens[i + 1].type, "outfile") != 0)))
//         {
//             printf("Mini: There's no output file in front of red out [%s]\n",parse->tokens[i].token);
//             return (TRUE);
//         }
//         // // if there's no appended file to be redirected 
//         else if ((ft_strcmp(parse->tokens[i].type, "append") == 0 && !parse->tokens[i + 1].token) || (ft_strcmp(parse->tokens[i].type, "append") == 0 && (ft_strcmp(parse->tokens[i + 1].type, "app_outfile") != 0)))
//         {
//             printf("Mini: There's no appended file in front of a append [%s]\n", parse->tokens[i].token);
//             return (TRUE);
//         }
//         // if there's no input file to be readead from 
//         else if ((ft_strcmp(parse->tokens[i].type, "red_input") == 0 && !parse->tokens[i + 1].token) || ((ft_strcmp(parse->tokens[i].type, "red_input") == 0) && (ft_strcmp(parse->tokens[i + 1].type, "infile") != 0)))
//         {
//             printf("Mini: There's no input file to be readead from [%s]\n", parse->tokens[i].token);
//             return (TRUE);            
//         }
//         i++;
//     }
// 	return FALSE;
// }