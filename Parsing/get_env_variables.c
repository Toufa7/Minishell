/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_variables.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchfa <abouchfa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 22:32:28 by otoufah           #+#    #+#             */
/*   Updated: 2022/07/26 17:43:53 by abouchfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	untill_this(char *var)
{
	int	i;

	i = -1;
	while (var[++i])
	{
		while (var[i] == '$')
			i++;
		if (!(ft_isalpha(var[i]) || (ft_isdigit(var[i]) && i != 0) || var[i] == '_'))
			break;
	}
	return (i);
}

char	*string_formating(char *str)
{
	int 	i = -1;
	int 	j = -1;
	int		quotes = 0;
	int		dollar = 0;
	int		pipe = 0;
	char	*string;
	while (str[++i])
	{
		if (str[i] == '"')
			quotes++;	
		else if (str[i] == '$')
			dollar++;
		else if (str[i] == '|')
			pipe++;
	}
	string = malloc(sizeof(char) * ft_strlen(str) + (quotes * 2) + dollar + pipe + 1); 
	if (!string)
		return (NULL);
	i = -1;
	while (str[++i])
	{
		if (str[i] == '"' && i != 0)
		{
			string[++j] = ' ';
			string[++j] = str[i];
			string[++j] = ' ';
		}
		else if ((str[i] == '$' && str[i - 1] != ' '))
			string[++j] = str[i];			
		else if ((str[i] == '$' && str[i - 1] != sing_quotes) || str[i] == '|')
		{
			string[++j] = ' ';
			string[++j] = str[i];
		}
		else
			string [++j] = str[i];
	}
	string[j + 1] = '\0';
	printf("formated_string -> |%s|\n",string);
	free(str);
	return (string);
}

char    *valid_input(char *str)
{
    int i = 0;
    int j = 0;
    char *var;
    var = malloc(sizeof(char) * ft_strlen(str - (ft_strlen(str) - untill_this(str))) + 1);
    while (str[i] && j < untill_this(str) - 1)
    {
        while (str[i] == '$')
            i++;
        var[j] = str[i];
        j++;
        i++;
    }
    var[j] = '\0';
    free(str);
    return (var);
}

char	*get_env_variables(char *target)
{
	int	i;
	int j;
	char **splt;

	i = -1;
	size_t k = 0;
	splt = ft_split(string_formating(target),  ' ');
	while (splt[++i])
	{
		while (splt[i][k] == '"')
		{
			k++;
			if (k == ft_strlen(splt[i]))
				i++;
		}
		target = ft_strjoin(valid_input(splt[i]), "=");
		printf("Target -> %s\n", target);
		j = -1;
		while (genv[++j])
		{
			if (ft_strncmp(target, genv[j], ft_strlen(target)) == 0)
			{
				printf("%s\n", (genv[j] + ft_strlen(target)));
					break;
			}
		}
	}
	return ("");
}


int main(int a, char **b, char **env)
{
	env_dup(env);
	while (1)
	{
		char *s = readline("");
		printf("%s", get_env_variables(s));
	}
}