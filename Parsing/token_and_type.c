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

	i = 0;
	while (parse->pipe_tokens[i])
	{
		printf("Token -> %s -> Type -> %s\n",
			parse->pipe_tokens[i]->token, parse->pipe_tokens[i]->type);
		i++;
	}
}
