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

<<<<<<< HEAD
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
=======
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
>>>>>>> bcf8e2cd257b7df216aee19117a7e90bf34da3ff

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
<<<<<<< HEAD
	free(str);
	printf("Formated String -> %s\n",string);
=======
	// free(str);
>>>>>>> bcf8e2cd257b7df216aee19117a7e90bf34da3ff
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
<<<<<<< HEAD
				printf("%s\n", (env[j] + ft_strlen(target)));
=======
				printf("%s\n", (env[j] + ft_strlen(s_format)));
>>>>>>> bcf8e2cd257b7df216aee19117a7e90bf34da3ff
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
<<<<<<< HEAD
		char *str = get_env_variables(env ,readline(""));
		printf("%s\n",str);
	}
}



=======
		printf("%s\n", get_env_variables(env, readline("")));
		// printf("%d\n", till_this(str));
	}
}

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
>>>>>>> bcf8e2cd257b7df216aee19117a7e90bf34da3ff
