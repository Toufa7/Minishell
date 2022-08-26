/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otoufah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 19:56:17 by otoufah           #+#    #+#             */
/*   Updated: 2022/08/26 19:56:18 by otoufah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	token_and_type(t_parse *parse)
{
	int	i;

	i = -1;
	while (parse->tokens[++i].token)
	{
		printf("Token -> %s -> Type -> %s\n",
			parse->tokens[i].token, parse->tokens[i].type);
	}
}
