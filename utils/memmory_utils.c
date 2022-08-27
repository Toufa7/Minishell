/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memmory_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchfa <abouchfa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 01:22:42 by abouchfa          #+#    #+#             */
/*   Updated: 2022/08/27 14:51:27 by abouchfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*list;

	list = malloc(sizeof(t_list));
	if (!list)
		return (NULL);
	list->content = content;
	list->next = NULL;
	return (list);
}

// void	ft_lstclear(t_list **lst, void (*del)(void*))
// {
// 	t_list	*temp;

// 	while (*lst)
// 	{
// 		temp = (*lst)->next;
// 		if (*lst && (*lst)->content)
// 			free((*lst)->content);
// 		if (*lst)
// 			free(*lst);
// 		(*lst) = temp;
// 	}
// }

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (!new)
		return ;
	if (*lst)
		new->next = *lst;
	*lst = new;
}

void	*alloc(size_t size)
{
	void	*content;
	
	content = malloc(size);
	ft_lstadd_front(global_data.alloc_list, ft_lstnew(content));
	return (content);
}