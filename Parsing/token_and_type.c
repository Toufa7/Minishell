/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_and_type.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchfa <abouchfa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 19:56:17 by otoufah           #+#    #+#             */
/*   Updated: 2022/08/31 18:36:57 by abouchfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	token_and_type(t_token **tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
	{
		printf("Token -> %s | Type -> %s\n",
			tokens[i]->token, tokens[i]->type);
		i++;
	}
}
