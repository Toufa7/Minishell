/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_variables.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchfa <abouchfa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 22:32:28 by otoufah           #+#    #+#             */
/*   Updated: 2022/08/14 15:15:01 by abouchfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*until_dollar(char *str, int *quot)
{
	int	i;

	i = 0;
	if (str[i] == '$')
		return (ft_strdup("$"));
	while (str[i] && str[i] != '$')
	{
		i++;
		if (!*quot && (str[i] == SING_QUOTES))
			*quot = SING_QUOTES;
		else if(*quot && (str[i] == *quot))
			*quot = 0;
	}
	return (ft_substr(str, 0, i));
}

char	*get_env_variables(char *target)
{
	int		i;
	char	*output;
	char	*variable;
	int		expa = 0;
	i = 0;
	output = ft_strdup("");
	while (target[i])
	{
		if (!expa && target[i] == SING_QUOTES)
			expa = SING_QUOTES;
		else if (expa && target[i] == expa)
			expa = 0;
		if (target[i] == '$' && !expa)
		{
			if (target[i + 1] == '?')
			{
				variable = ft_itoa(global_data.errno_cp);
				output = ft_strjoin(output, variable);
				i += 2;
			}
			else
			{
				variable = ft_substr(target + i + 1, 0, validate_var_name(target + i + 1));
				output = ft_strjoin(output, getenv(variable));
				i += validate_var_name(target + i + 1) + 1;
			}
		}
		else
		{
			variable = until_dollar(target + i, &expa);
			i += ft_strlen(variable);
			output = ft_strjoin(output, variable);
		}
		printf("%zu\n",ft_strlen(output));
		// free_str(variable);
	}
	// free_str(target);
	return output;
}





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
