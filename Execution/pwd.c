#include "../Parsing/minishell.h"

void    pwd(void)
{
    char    buff[PATH_MAX];

    if (getcwd(buff, sizeof(buff)) != NULL)
    {
        printf("%s\n", buff);
    }
    else
        perror("Can't getting the current working directory");
} 


// We must allocate the cwdbuf buffer to be at least size bytes in length.
// (Normally, we would size cwdbuf using the PATH_MAX constant.)

// To get the working directory

// Getting pathnames