/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spliting_with_spaces.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otoufah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 22:34:59 by otoufah           #+#    #+#             */
/*   Updated: 2022/07/02 22:35:00 by otoufah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char    *handling_quotes(char *str)
{
    int i = -1;
    char *dup = malloc(sizeof(char) * ft_strlen(str) + 1);
    if (!dup)
        return (NULL);
    while (str[++i])
    {
        if (str[i] == ' ')
            dup[i] = '%';
        else
            dup[i] = str[i];
    }
    dup[i] = '\0';
    return (dup);
}

t_tokens	*spliting_with_spaces(char *str)
{
	int			i;
	char		**line;
	t_tokens	*tokens;

	i = 0;
	line = ft_split(str, ' ');
	while (line[i])
		i++;
	tokens = malloc(sizeof(t_tokens) * (i + 1));
	i = -1;
	while (line[++i])
		tokens[i].token = line[i];
	tokens[i].token = NULL ;
	return (tokens);
}