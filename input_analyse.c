#include "minishell.h"

void    input_analyse(t_tokens *tokens)
{
    int i = -1;
    char *red_input = "<";
    char *here_doc = "<<";
    char *red_out = ">";
    char *append = ">>";

    while (tokens[++i].token)
    {
        if (ft_strcmp(tokens[i].token,red_input) == 0)
            tokens[i].type = "red_input";
        else if (ft_strcmp(tokens[i].token,red_out) == 0)
            tokens[i].type = "red_out";
        else if (ft_strcmp(tokens[i].token,here_doc) == 0)
            tokens[i].type = "here_doc";
        else if (ft_strcmp(tokens[i].token,append) == 0)
            tokens[i].type = "append";
        else
            tokens[i].type = "None";

        if (i == 0 && ft_strcmp(tokens[0].type, "None") == 0)
            tokens[i].type = "command";
        else if (i == 0)
            continue ;
        else if (ft_strcmp(tokens[i - 1].type, "red_input") == 0)
            tokens[i].type = "infile";
        else if (ft_strcmp(tokens[i - 1].type, "red_out") == 0)
            tokens[i].type = "outfile";
        else if (ft_strcmp(tokens[i - 1].type, "append") == 0)
            tokens[i].type = "app_outfile";
        else if (ft_strcmp(tokens[i - 1].type, "here_doc") == 0)
            tokens[i].type = "doc_infile";
        else if (ft_strcmp(tokens[i].type, "None") == 0)
            tokens[i].type = "command";
    }
}

