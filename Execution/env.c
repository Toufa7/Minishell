#include <stdio.h>
#include <string.h>

char    **envi(char **env)
{
    char **my_env;
    int sum = 0;
    int i = -1;

    while (env[++i])
        sum += strlen(env[i]);
    i = -1;
    while (env[++i])
    {
        my_env[i] = env[i];
    }
    return (my_env); 
}

int main(int ac, char **av, char **environ)
{
    int i = -1;
    char **hola = envi(environ);
    while (hola[++i])
    {
        printf("%s\n",hola[i]);
    }

}
