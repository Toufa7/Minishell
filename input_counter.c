#include "minishell.h"

void   input_counter(t_tokens *tokens)
{
    int i = 0;
    while (tokens[i].token)
    {
        if (ft_strcmp(tokens[i].type ,"red_input") == 0)
            tokens->red_in++;
        else if (ft_strcmp(tokens[i].type ,"red_out") == 0)
            tokens->red_out++;
        else if (ft_strcmp(tokens[i].type ,"here_doc") == 0)
            tokens->here_do++;
        else if (ft_strcmp(tokens[i].type ,"append") == 0)
            tokens->app++;
        else if (ft_strcmp(tokens[i].type ,"command") == 0)
            tokens->cmd++;
        else if (ft_strcmp(tokens[i].type ,"infile") == 0)
            tokens->in_file++;
        else if (ft_strcmp(tokens[i].type ,"outfile") == 0)
            tokens->out_file++;
        else if (ft_strcmp(tokens[i].type ,"app_outfile") == 0)
            tokens->app_file++;
        else if (ft_strcmp(tokens[i].type ,"doc_infile") == 0)
            tokens->doc_file++;
        i++;
    }
}