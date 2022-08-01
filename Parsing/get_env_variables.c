/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_variables.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchfa <abouchfa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 22:32:28 by otoufah           #+#    #+#             */
/*   Updated: 2022/08/01 12:27:43 by abouchfa         ###   ########.fr       */
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
		if (!(ft_isalpha(var[i]) || (ft_isdigit(var[i]) && i != 0)
				|| var[i] == '_'))
			break ;
	}
	return (i);
}

char	*string_formating(char *str)
{
	int		i;
	int		j;
	int		quotes;
	int		dollar;
	int		pipe;
	char	*string;

	i = -1;
	j = -1;
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
		else if ((str[i] == '$' && i != 0) || str[i] == '|')
		{
			string[++j] = ' ';
			string[++j] = str[i];
		}
		else if (str[i] == sing_quotes)
		{
			string[++j] = str[i++];
			while (str[i] != sing_quotes)
			{
				string[++j] = str[i];
				i++;
			}
			string[++j] = str[i];
		}
		else
			string [++j] = str[i];
	}
	string[j + 1] = '\0';
	printf("Formated String -> %s\n", string);
	free(str);
	return (string);
}

char	*valid_input(char *str)
{
	int		i;
	int		j;
	char	*var;

	i = 0;
	j = 0;
	if (!str)
		return ("");
	var = malloc(sizeof(char) * ft_strlen(str - (ft_strlen(str) - untill_this(str))) + 1);
	while (str[i] && j < untill_this(str))
	{
		while (str[i] == '$'){
			i++;
		}
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
	int		i;
	int		j;
	int		k;
	char	**splt;

	i = -1;
	k = 0;
	splt = ft_split(string_formating(target), ' ');
	while (splt[++i])
	{
		while (splt[i][k] == '"')
		{
			k++;
			if ((size_t)k == ft_strlen(splt[i]))
				i++;
		}
		target = ft_strjoin(valid_input(splt[i]), "=");
		printf("Target -> %s\n",target);
		j = -1;
		while (global_data.envp[++j])
		{
			if (ft_strncmp(target, global_data.envp[j], ft_strlen(target)) == 0)
			{
				// return (ft_strdup(global_data.envp[j] + ft_strlen(target)));
				printf("%s\n", global_data.envp[j] + ft_strlen(target));
				break ;
			}
		}
		free_str(target);
	}
	return ("");
}

int main(int a, char **b, char **env)
{
	env_dup(env);
	while (1)
	{
		char *s = readline("");
		printf("%s\n", get_env_variables(s));
		// system("leaks a.out");
	}
}