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

#include "minishell.h"

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

	i = 0;
	target = ft_strjoin(variable(target), "=");
	while (env[i])
	{
		if (ft_strstr(env[i], target))
		{
			return (env[i] + ft_strlen(target));
		}
		i++;
	}
	return ("\n");
}

/*


  307  echo lol$USER jsdhidcg$TEMP
  308  echo lol$USER jsdhidcg$PWD
  309  echo lol$USER jsdhidcg'$PWD'
  310  echo lol$USER jsdhidcg"$PWD"
  311  echo lol$USERjsdhidcg$PWD
  312* echo $USER
  313  echo lol$USERjsdhidcg$PWDfu
  314  echo $lol$USERjsdhidcg$PWDfu
  315  echo "$lol$USERjsdhidcg$PWDuy"
  316  echo $lol"$USER"jsdhidcg$PWDuy
  317  echo lol"$USER"jsdhidcg$PWDuy
  318  echo lol"$USER"jsdhidcg"$PWD"uy
  319  echo lol"$USER"jsdhidcg'$PWD'uy
  320  echo lol"$USER"jsdhidcg$PWDuy
*/
