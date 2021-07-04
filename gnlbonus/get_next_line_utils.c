/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narakely <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/07 14:54:01 by narakely          #+#    #+#             */
/*   Updated: 2021/02/14 15:09:05 by narakely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_list	*ft_lstnew(void *content)
{
	t_list		*list;
	char		c;

	if (!(list = malloc(sizeof(t_list*) * 1)))
		return (NULL);
	c = *(char*)content;
	(*list).content = c;
	list[0].next = NULL;
	return (list);
}

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list *temp;

	temp = *lst;
	if (lst)
	{
		if (*lst == NULL)
			*lst = new;
		else
		{
			while (temp->next)
			{
				temp = temp->next;
			}
			temp->next = new;
		}
	}
}

void	ft_lstclear(t_list **lst)
{
	t_list *temp;

	if (lst)
	{
		while (*lst)
		{
			temp = (*lst)->next;
			ft_lstdelone(*lst);
			(*lst) = temp;
		}
		lst = NULL;
	}
}

void	ft_lstdelone(t_list *lst)
{
	if (lst)
	{
		free(lst);
		lst = NULL;
	}
}

int		ft_lstsize(t_list *lst)
{
	int		length;
	t_list	*temp;

	length = 0;
	temp = lst;
	if (temp == NULL)
		return (length);
	while (temp->next != NULL)
	{
		length++;
		temp = temp->next;
	}
	if (temp->next == NULL)
		length++;
	return (length);
}
