/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_perror.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchfa <abouchfa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 08:41:50 by abouchfa          #+#    #+#             */
/*   Updated: 2022/09/01 08:50:43 by abouchfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_perror(char *str, t_bool exitt)
{
	ft_putstr_fd("Mini: ", 2);
	perror(str);
	g_data.errno_cp = errno;
	if (exitt)
		exit(errno);
}
