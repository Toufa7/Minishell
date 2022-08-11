/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_variables.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchfa <abouchfa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 22:32:28 by otoufah           #+#    #+#             */
/*   Updated: 2022/08/02 12:46:03 by abouchfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*until_dollar(char *str)
{
	int i = 0;

	while (str[i] && str[i] != '$')
		i++;
	return (ft_substr(str, 0, i));
}

char	*get_env_variables(char *target)
{
	int		i;
	char	*output;
	char	*variable;

	i = 0;
	output = ft_strdup("");
	while (target[i])
	{
		if (target[i] == '$')
		{
			variable = ft_substr(target + i + 1, 0, validate_var_name(target + i + 1));
			output = ft_strjoin(output, getenv(variable));
			i += validate_var_name(target + i + 1) + 1;
		}
		else
		{
			variable = until_dollar(target + i);
			i += ft_strlen(variable);
			output = ft_strjoin(output, variable);
			
		}
	}
	free_str(target);
	return output;
}


// int main(int a, char **b, char **env)
// {
// 	env_dup(env);
// 	while (1)
// 	{
// 		char *s = readline("");
// 		printf("%s\n", get_env_variables(s));
// 	}
// }




// dhjhjfh'e'jhdg"hjg  678 iu6 n mjhjy" | 'jhjkx "iuysi " dhk  " ' | iuy ""iuy '' kjhy "|jkd $HOME'e'| dfv " 


// dhjhjfhejhdghjg  678 iu6 n mjhjy | jhjkx "iuysi " dhk  "  | iuy iuy  kjhy |jkd otoufah'e'| dfv 

// 'e'"c"$hjhjhjhjhj"o" hi

//h  b v b " $gg '$HOME.anaomarli3ndo ....'"


/*
echo lol$USER jsdhidcg$TEMP
echo lol$USER jsdhidcg$PWD
echo lol$USER jsdhidcg'$PWD'
echo lol$USER jsdhidcg"$PWD"
echo lol$USERjsdhidcg$PWD
echo $USER
echo lol$USERjsdhidcg$PWDfu
echo $lol$USERjsdhidcg$PWDfu
echo "$lol$USERjsdhidcg$PWDuy"
echo $lol"$USER"jsdhidcg$PWDuy
echo lol"$USER"jsdhidcg$PWDuy
echo lol"$USER"jsdhidcg"$PWD"uy
echo lol"$USER"jsdhidcg'$PWD'uy
echo lol"$USER"jsdhidcg$PWDuy
*/
