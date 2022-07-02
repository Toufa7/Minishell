#include "minishell.h"

void    input_types(t_parse *parse)
{
    int i = 0;
    while (parse->tokens[i].token)
    {
        if (ft_strcmp(parse->tokens[i].token, "outfile") == 0)
        {   
            parse->input[i].out_files = parse->tokens[i].token;
        }
        else if (ft_strcmp(parse->tokens[i].token, "doc_infile") == 0)
        {
            parse->input[i].doc_infile = parse->tokens[i].token;
        }
        else if (ft_strcmp(parse->tokens[i].token, "app_outfile") == 0)
        {
            parse->input[i].app_outfile = parse->tokens[i].token;
        }
        else if (ft_strcmp(parse->tokens[i].token, "command") == 0)
        {
            parse->input[i].command = parse->tokens[i].token;
        }
        i++;
    }
}
