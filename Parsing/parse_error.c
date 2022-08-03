#include "../minishell.h"

/*
TODO:
    - Man errno ?
*/


bool    parse_error(t_parse *parse)
{
    int i = 0;
    while ((size_t )i < parse->tokens->total && parse->tokens[i].token)
    {
        // printf("Next -> %s\n",parse->tokens[i].type);

        if ((!parse->tokens[i + 1].token && (ft_strcmp(parse->tokens[i].type, "red_out") == 0)) || (ft_strcmp(parse->tokens[i].type, "red_out") == 0 && ft_strcmp(parse->tokens[i + 1].type, "outfile") != 0))
			return TRUE;
        // else if (!parse->tokens[i + 1].token || (ft_strcmp(parse->tokens[i].type, "append") == 0 && ft_strcmp(parse->tokens[i + 1].type, "app_outfile") != 0))          
        // {
        //     global_data.err = 1;
        //     printf("Error\n");
        // }
        // else if (!parse->tokens[i + 1].token || (ft_strcmp(parse->tokens[i].type, "here_doc") == 0 && ft_strcmp(parse->tokens[i + 1].type, "delimiter") != 0))
        // {
        //     global_data.err = 1;
        //     printf("Error\n");
        // }
        i++;
    }
	return FALSE;
}




/*
Examples :

    - > without ouputfile
    - < without pipe_data
    - 

*/