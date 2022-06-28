#ifndef MINI_H
# define MINI_H

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "./Libft/libft.h"

#define GREEN "\033[32m"
#define RESET "\033[0m"
#define True 1


char    *get_env_variables(char **env, char *target);
char    **pipes(char *str);

#endif