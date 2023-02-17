/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memmory_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchfa <abouchfa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 01:22:42 by abouchfa          #+#    #+#             */
/*   Updated: 2022/09/03 02:16:24 by abouchfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_alloc_lst	*ft_lstnew(void *content)
{
	t_alloc_lst	*list;

	list = malloc(sizeof(t_alloc_lst));
	if (!list)
		return (NULL);
	list->content = content;
	list->next = NULL;
	return (list);
}

void	ft_lstadd_front(t_alloc_lst	**lst, t_alloc_lst	*new)
{
	if (!new)
		return ;
	if (*lst)
		new->next = *lst;
	*lst = new;
}

void	*alloc(size_t size, char *source)
{
	void	*content;

	(void) source;
	content = malloc(size);
	if (!content)
	{
		perror("");
		exit(errno);
	}
	ft_lstadd_front(g_data.alloc_list, ft_lstnew(content));
	return (content);
}
