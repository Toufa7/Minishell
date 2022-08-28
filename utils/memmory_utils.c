/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memmory_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchfa <abouchfa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 01:22:42 by abouchfa          #+#    #+#             */
/*   Updated: 2022/08/27 16:26:26 by abouchfa         ###   ########.fr       */
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

void    ft_lstadd_back(t_list **lst, t_list *new)
{
    t_list  *temp;
	// printf("-1\n");
    if (!new)
            return ;
	// printf("-2\n");
    if (!*lst)
    {
	// printf("-3\n");
        *lst = new;
        return ;
    }
	// printf("-4\n");
    temp = *lst;
    while (temp->next)
        temp = temp->next;
	// printf("-5\n");
    temp->next = new;
}

void	*alloc(size_t size)
{
	void	*content;
	
	content = malloc(size);
	ft_lstadd_back(g_data.alloc_list, ft_lstnew(content));
	return (content);
}

