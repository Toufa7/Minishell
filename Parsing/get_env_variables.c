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
	int		dollar;
	int		pipe;
	char	*string;

	i = -1;
	quotes = 0;
	dollar = 0;
	pipe = 0;
	while (str[++i])
	{
		if (str[i] == '"')
			quotes++;	
		else if (str[i] == '$')
			dollar++;
		else if (str[i] == '|')
			pipe++;
	}
	// printf("nb quotes : %d nb dollars : %d\n", quotes, dollar);
	string = malloc(sizeof(char) * ft_strlen(str) + (quotes * 2) + dollar + pipe + 1); 
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
		else if (str[i] == '$' || str[i] == '|')
		{
			string[++j] = ' ';
			string[++j] = str[i];
		}
		else
			string [++j] = str[i];
	}
	string[j + 1] = '\0';
	// printf("Formated String -> %s\n", string);
	// free(str);
	return (string);
}

// int		till_this(char *str)
// {
// 	int i = -1;
// 	while (str[++i])
// 		if (str[i] < 'a' && str[i] > 'z') || 
// 			return (i);
// 	return (-1);
// }

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

char	*get_env_variables(char *target)
{
	int	i;
	int j;
	char **splt;

	i = -1;
	splt = ft_split(string_formating(target),  ' ');
	while (splt[++i])
	{
		target = ft_strjoin(variable(splt[i]), "=");
		j = -1;
		while (genv[++j])
		{
			if (ft_strstr(genv[j], target))
			{
				printf("%s\n", (genv[j] + ft_strlen(target)));
					break;
			}
		}
	}
	return ("");
}

// int main(int a, char **b, char **env)
// {
// 	env_dup(env);
// 	while (1)
// 	{
// 		char *s = readline("");
// 		printf("%s\n",get_env_variables(s));
// 	}
// }