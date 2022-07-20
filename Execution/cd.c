#include "../Parsing/minishell.h"

void    cd()
{
    chdir("..");
}

void    pwd(void)
{
    char    *buff;

    if (getcwd(buff, sizeof(buff)) != NULL)
    {
        printf("%s\n", buff);
    }
    else
        perror("Can't getting the current working directory");
} 

// Returns 0 on success, or –1 on error

int main()
{
    pwd();
    printf("---\n");
    chdir("/Users/otoufah/Desktop/Minishell");
    pwd();
}