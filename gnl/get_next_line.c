/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narakely <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/07 14:14:17 by narakely          #+#    #+#             */
/*   Updated: 2021/02/14 15:05:40 by narakely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	get_next_line(int fd, char **line)
{
	static char	c;
	t_list		*list;
	t_list		*temp;
	int			ir[2];

	list = NULL;
	while ((ir[1] = read(fd, &c, 1)) && c != '\n')
	{
		if (ir[1] == -1 || fd < 0 || !line || BUFFER_SIZE <= 0)
			return (-1);
		ft_lstadd_back(&list, ft_lstnew(&c));
	}
	temp = list;
	if (!((*line) = (char*)malloc(sizeof(char*) * (ft_lstsize(list) + 1))))
		return (-1);
	ir[0] = 0;
	while (temp)
	{
		(*line)[ir[0]++] = temp->content;
		temp = temp->next;
	}
	ft_lstclear(&list);
	(*line)[ir[0]] = '\0';
	return (ir[1] == 0 ? 0 : 1);
}
