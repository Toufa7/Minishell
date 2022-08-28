/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memmory_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchfa <abouchfa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 01:22:42 by abouchfa          #+#    #+#             */
/*   Updated: 2022/08/28 16:39:27 by abouchfa         ###   ########.fr       */
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

void    ft_lstadd_front(t_alloc_lst **lst, t_alloc_lst *new)
{
    if (!new)
        return ;
    if (*lst)
        new->next = *lst;
    *lst = new;
}

void	*alloc(size_t size, char *source)
{
	(void) source;
	void	*content;
	
	printf("Size: %zu | Source: %s\n", size, source);
	content = malloc(size);
	ft_lstadd_front(g_data.alloc_list, ft_lstnew(content));
	return (content);
}

