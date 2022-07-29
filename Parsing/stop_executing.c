#include "../minishell.h"

/*
TODO:
    - Man errno ?
*/


int     stop_executing(t_parse *parse)
{
    int i = -1;
    
    parse->input->parse_error = 0;
    while (parse->tokens[++i].type)
    {
        if (ft_strcmp(parse->tokens[i].type, "red_out") == 0 && !parse->input->out_files)
            parse->input->parse_error = 1;
        // else if (ft_strcmp(parse->tokens[i].type, "append") == 0 && !parse->input->app_outfile)             
        //     parse->input->parse_error = 1;    
    }      
    return (parse->input->parse_error);
}



/*
Examples :

    - > without ouputfile
    - < without input
    - 

*/