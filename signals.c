#include "minishell.h"

char    *get_line()
{
    char *line;

    line = NULL;
    if (line)
    {
        free(line);
        line = NULL;
    }
    line = readline("Minishell>");
    if (line)
        add_history(line);
    return (line);
}

void    sig_handler(int signum)
{
    if (signum == SIGINT)
    {
        printf("\n");
        rl_replace_line("", 0);
        rl_on_new_line();
        rl_redisplay();
    }
}

int main(void)
{
    char    *line;

    signal(SIGINT, sig_handler);
    line = get_line();
    printf("%s\n", line);
}