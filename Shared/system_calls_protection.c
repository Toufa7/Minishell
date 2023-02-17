/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   system_calls_protection.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchfa <abouchfa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 20:04:29 by otoufah           #+#    #+#             */
/*   Updated: 2022/09/03 03:51:22 by abouchfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	open_heredoc_file(t_bool read_only)
{
	int	fd;

	if (read_only)
		fd = open(g_data.heredoc_file, O_RDWR, 0004);
	else
		fd = open(g_data.heredoc_file, O_CREAT | O_RDWR | O_TRUNC, 0777);
	if (fd == -1)
	{
		perror("");
		exit(1);
	}
	return (fd);
}

void	ft_close(int n, int s)
{
	(void) s;
	if (n > 2)
		close(n);
}

int	ft_fork(void)
{
	int	id;

	id = fork();
	if (id == -1)
	{
		perror("");
		exit(1);
	}
	return (id);
}

void	free_str(void *ptr)
{
	if (ptr)
		free(ptr);
}

void	free_arr(void **arr)
{
	int	i;

	i = -1;
	while (arr && arr[++i])
		free_str(arr[i]);
	free(arr);
}
