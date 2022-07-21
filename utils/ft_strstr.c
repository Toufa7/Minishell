/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchfa <abouchfa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 20:05:33 by otoufah           #+#    #+#             */
/*   Updated: 2022/07/21 10:22:30 by abouchfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	size_t		i;
	size_t		j;
	char		*hay;

	hay = (char *)haystack;
	if (!needle)
		return (NULL);
	if (needle[0] == 0)
		return (hay);
	i = 0;
	while (hay[i])
	{
		j = 0;
		while (hay[i + j] == needle[j])
		{
			if (needle[j + 1] == 0)
				return (&hay[i]);
			j++;
		}
		i++;
	}
	return (NULL);
}

// int main()
// {
// 	printf("%s\n",ft_strstr("TMPDIR=/var/folders/zz/zyxvpxvq6csfxvn_n0000jg00004br/T/",NULL));
// }

