/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_variables.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchfa <abouchfa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 22:32:28 by otoufah           #+#    #+#             */
/*   Updated: 2022/07/23 16:56:30 by abouchfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
FIXME:
	$PWD problem greping OLDPWD
*/ 

// int	ft_isalpha(int c)
// {
// 	if ((c >= 65 && c <= 90) || ((c >= 97 && c <= 122)))
// 		return (1);
// 	else
// 		return (0);
// }

// int	ft_isdigit(int c)
// {
// 	if (c >= 48 && c <= 57)
// 		return (1);
// 	else
// 		return (0);
// }

char	*string_formating(char *str)
{
	int 	i;
	int 	j;
	int		quotes;
	char	*string;

	i = -1;
	quotes = 0;
	while (str[++i])
	{
		if (str[i] == '"' || str[i] == '$')
			quotes++;	
	}
	printf("nb quotes : %d\n", quotes);
	string = malloc(sizeof(char) * ft_strlen(str) + (quotes * 2) + 1); 
	if (!string)
		return (NULL);
	i = -1;
	j = -1;
	while (str[++i])
	{
		if (str[i] == '"')
		{
			string[++j] = ' ';
			string[++j] = str[i];
			string[++j] = ' ';
		}
		else if (str[i] == '$')
		{
			string[++j] = str[i];
			string[++j] = ' ';
		}
		else
			string [++j] = str[i];
	}
	string[j + 1] = '\0';
	free(str);
	printf("Formated String -> %s\n",string);
	return (string);
}

char	*variable(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			return (&str[i + 1]);
		i++;
	}
	return (NULL);
}

char	*get_env_variables(char **env, char *target)
{
	int	i;
	int j;
	char **splt;
	char *s_format;

	i = -1;
	splt = ft_split(string_formating(target),  ' ');
	while (splt[++i])
	{
		target = ft_strjoin(variable(splt[i]), "=");
		j = -1;
		while (env[++j])
		{
			if (ft_strstr(env[j], target))
			{
				printf("%s\n", (env[j] + ft_strlen(target)));
					break;
			}
		}
	}
	return ("");
}

int main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	while (1)
	{
		char *str = get_env_variables(env ,readline(""));
		printf("%s\n",str);
	}
}



