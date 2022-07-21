/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_variables.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otoufah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 22:32:28 by otoufah           #+#    #+#             */
/*   Updated: 2022/07/02 22:32:29 by otoufah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*string_formating(char *str)
{
	int i;
	int j;
	int how = 0;
	i = -1;
	while (str[++i])
	{
		if (str[i] == '"')
		{
			how++;
		}
	}
	char *new = malloc(sizeof(char ) * ft_strlen(str) + (how * 2) + 1);
	if (!new)
		return (NULL);
	i = -1;
	j = -1;
	while (str[++i])
	{
		if (str[i] == '"')
		{
			new[++j] = ' ';
			while (str[i] != '"')
				new[++j] = str[i];
			new[++j] = ' ';
		}
		else
			new[++j] = str[i];
	}
	return (new);
}


// char	*variable(char *str)
// {
// 	int	i;

// 	i = 0;
// 	while (str[i])
// 	{
// 		if (str[i] == '$')
// 			return (&str[i + 1]);
// 		i++;
// 	}
// 	return (NULL);
// }

// char	*get_env_variables(char **env, char *target)
// {
// 	int	i;
// 	int j;
// 	char **splt;
// 	char *pwd;

// 	i = -1;
// 	splt = ft_split(target, ' ');
// 	while (splt[++i])
// 	{
// 		target = ft_strjoin(variable(splt[i]), "=");
// 		printf("Target -> %s\n", target);
// 		j = -1;
// 		while (env[++j])
// 		{
// 			if (ft_strstr(env[j], target))
// 				printf("%s\n", (env[j] + ft_strlen(target)));
// 		}
// 	}
// 	return ("");
// }

int main(int ac, char **av, char **env)
{
	while (1)
	{
		char *str = readline("");
		printf("%s\n", string_formating(str));
	}
}