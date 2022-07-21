/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_variables.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchfa <abouchfa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 22:32:28 by otoufah           #+#    #+#             */
/*   Updated: 2022/07/21 11:40:21 by abouchfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
			string[++j] = ' ';
			string[++j] = str[i];
		}
		else
			string [++j] = str[i];
	}
	string[j + 1] = '\0';
	free(str);
	return (string);
}

char	*variable(char *str)
{
	int i;
	int how = 0;
	i = -1;
	while (str[++i])
	{
		if (str[i] == '"')
		{
			how++;
		}
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
	s_format = string_formating(target);
	printf("Format -> %s\n",s_format);
	splt = ft_split(s_format,  ' ');
	while (splt[++i])
	{
		target = ft_strjoin(variable(splt[i]), "=");
		j = -1;
		while (env[++j])
		{
			if (ft_strstr(env[j], target))
				printf("%s\n", (env[j] + ft_strlen(target)));
		}
	}
	return ("");
}

// int main(int ac, char **av, char **env)
// {
// 	while (1)
// 	{
// 		char *str = readline("");
// 		printf("%s\n", get_env_variables(env ,str));
// 	}
// }