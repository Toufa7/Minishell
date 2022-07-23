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

int	ft_isalpha(int c)
{
	if ((c >= 65 && c <= 90) || ((c >= 97 && c <= 122)))
		return (1);
	else
		return (0);
}

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	else
		return (0);
}

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

int		till_this(char *str)
{
	int i = 0;
	while (ft_isalpha(str[i]) == 0 || ft_isdigit(str[i]) == 0)
		i++;
	return (i);
}

char	*variable(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '.')
	{
		if (str[i] == '$' && str[i + 1])
			return (&str[i + 1]);
		else
			return (NULL);
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
	s_format = string_formating(target);
	splt = ft_split(s_format,  ' ');
	while (splt[++i])
	{
		s_format = ft_strjoin(variable(splt[i]), "=");
		printf("s_format -> %s\n",s_format);
		j = -1;
		while (env[++j])
		{
			if (ft_strstr(env[j], s_format))
			{
				printf("%s\n", (env[j] + ft_strlen(s_format)));
				break;
			}
		}
	}
	return ("");
}

// int main(int ac, char **av, char **env)
// {
// 	while (1)
// 	{
// 		char *str = readline("");
// 		add_history(str);
// 		printf("%d\n", till_this(str));
// 	}
// }


//	echo lol$USER jsdhidcg$TEMP
//	echo lol$USER jsdhidcg$PWD
//	echo lol$USER jsdhidcg'$PWD'
//	echo lol$USER jsdhidcg"$PWD"
//	echo lol$USERjsdhidcg$PWD
//	echo $USER
//	echo lol$USERjsdhidcg$PWDfu
//	echo $lol$USERjsdhidcg$PWDfu
//	echo "$lol$USERjsdhidcg$PWDuy"
//	echo $lol"$USER"jsdhidcg$PWDuy
//	echo lol"$USER"jsdhidcg$PWDuy
//	echo lol"$USER"jsdhidcg"$PWD"uy
//	echo lol"$USER"jsdhidcg'$PWD'uy
//	echo '$USER$LESS$LESS'
//	echo $USUS
//	echo '$USER'
//	echo $USER.oussama
//	echo $USERvcdwvw.oussama
//	echo $USERvcdwvw_oussama
//	echo $USERvcdwvw2oussama
//	echo $USERvcdwvwy\oussama
//	echo $USER\oussama
//	echo $USER;oussama
//	echo $USER[oussama
//	echo $USER,oussama
