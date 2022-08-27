/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchfa <abouchfa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 16:41:15 by otoufah           #+#    #+#             */
/*   Updated: 2022/08/27 14:27:16 by abouchfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_next_line(int fd)
{
	int		i;
	int		len;
	char	*temp;
	char	*line;
	char	buffer;

	line = NULL;
	buffer = 0;
	while (buffer != '\n' && read(fd, &buffer, 1) > 0)
	{
		i = -1;
		len = 0;
		temp = line;
		if (line)
			len = ft_strlen(line);
		line = alloc(len + 2);
		while (++i < len)
			line[i] = temp[i];
		if (buffer != '\n')
			line[i++] = buffer;
		line[i] = 0;
		if (temp)
			free(temp);
	}
	return (line);
}
