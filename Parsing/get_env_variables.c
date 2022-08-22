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

char	*add_equal(char *str)
{
	return (ft_strjoin(str,"="));
}
char	*until_dollar(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '$')
		return (ft_strdup("$"));
	while (str[i] && str[i] != '$')
		i++;
	return (ft_substr(str, 0, i));
}

char	*get_env_variables(char *target)
{
	int		i;
	int		idx;
	char	*output;
	char	*variable;
	char	*env_var;
	output = ft_strdup("");
	i = 0;
	while (target[i])
	{
		if (target[i] == '$' )
		{
			if (target[i + 1] == '?')
			{
				variable = ft_itoa(global_data.errno_cp);
				output = ft_strjoin(output, variable);
				i += 2;
			}
			else
			{
				// printf("Target -> %s\n",target);
				variable = ft_substr(target + i + 1, 0, validate_var_name(target + i + 1));
				env_var = add_equal(variable);
				idx = get_var_index(env_var);
				output = ft_strjoin(output, get_var_val(idx , FALSE));
				i += validate_var_name(target + i + 1) + 1;
			}
		}
		else
		{
			variable = until_dollar(target + i);
			i += ft_strlen(variable);
			output = ft_strjoin(output, variable);
		}
		free_str(variable);
	}
	free_str(target);
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
