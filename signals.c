#include "minishell.h"


void    signal_handler(int sognal)
{
    if (sognal == SIGINT)
    {
        printf("\n");
        rl_on_new_line();
        rl_replace_line("",0);
        rl_redisplay();
    }
    else if (sognal == SIGINT)
    {
        printf("You Pressed On Control + D\n");
    }
}

int main()
{
    while (1)
    {
        char *s = readline("Input -> ");
        signal(SIGINT, signal_handler);
        signal(SIGQUIT, signal_handler);
        signal(SIGINT, signal_handler);
    }
}