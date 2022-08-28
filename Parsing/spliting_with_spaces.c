/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spliting_with_spaces.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchfa <abouchfa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 22:34:59 by otoufah           #+#    #+#             */
/*   Updated: 2022/08/28 15:18:46 by abouchfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_tokens	*spliting_with_spaces(char *str)
{
	int			i;
	char		**line;
	t_tokens	*tokens;

	i = 0;
	line = ft_split(str, ' ');
	while (line[i])
		i++;
	tokens = alloc(sizeof(t_tokens) * (i + 1), "spliting_with_spaces");
	i = -1;
	while (line[++i])
		tokens[i].token = line[i];
	tokens[i].token = NULL;
	i = -1;
	return (tokens);
}
