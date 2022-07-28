#include "../minishell.h"

/*
TODO:
    - Man errno ?
*/


int     stop_executing(t_parse *parse)
{
    int i = -1;
    while (parse->tokens[++i].type)
    {
        if (ft_strcmp(parse->tokens[i].type, "red_out") == 0 && !parse->input->app_outfile)
            e
                    
    }
}



/*
Examples :

    - > without ouputfile
    - < without input
    - 

*/