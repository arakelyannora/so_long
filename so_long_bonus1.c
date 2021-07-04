/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narakely <narakely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 20:24:51 by narakely          #+#    #+#             */
/*   Updated: 2021/06/30 13:09:28 by narakely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"
#include "stdio.h"
//gcc -o so_long_bonus -lmlx -framework OpenGL -framework AppKit so_long_bonus.c gnl/get_next_line.c gnl/get_next_line_utils.c libft/libft.a
void	ft_putstr_fd(char *s, int fd)
{
	while (*s)
	{
		write(fd, s, 1);
		s++;
	}
}
int	ft_strlen(const char *s)
{
	int length;

	length = 0;
	while (*s)
	{
		length++;
		s++;
	}
	return (length);
}
int get_count(int fd, int* rows_length)
{
	char* line;
	int count;
	
	count = 0;
	*rows_length = 0;
	while (get_next_line(fd, &line))
	{
		if (count == 0)
			*rows_length = ft_strlen(line);
		if (ft_strlen(line) != *rows_length)
			return (-1);
		count++;
	}
	if (ft_strlen(line) != *rows_length)
			return (-1);
	count++;
	return (count);
}
void error(int fd, char *err_msg)
{
	ft_putstr_fd("ERROR\n", 1);
	ft_putstr_fd(err_msg, 1);
	close(fd);
	exit(1);
}
int	exit_collec_count(char line_j, t_comp *comp)
{
	if (line_j == 'E')
		comp->exit_cnt++;
	if (line_j == 'C')
		comp->coll_cnt++;
	if (line_j == 'P')
	{
		comp->play_cnt++;
		return (1);
	}
	if (line_j == 'M')
		comp->pol_cnt++;
	return (0);
}
int		check_map(int i, int row_count, int row_length, char *line, t_comp *comp)
{
	int j;

	j = 0;
	
	if (i == 0 || i == row_count - 1)
	{
		while (j < row_length)
		{
			if (line[j] != '1')
				return (1);
			j++;
		}
	}
	else {
		if (line[0] != '1' || line[row_length - 1] != '1')
			return (1);
		while (j < row_length)
		{
			if (line[j] != '1' && line[j] != '0' && 
			line[j] != 'E' && line[j] != 'C' && line[j] != 'P' && line[j] != 'M')
				return (2);
			else 
			{
				if (exit_collec_count(line[j], comp) == 1)
				{
					comp->pl_posx = j;
					comp->pl_posy = i;
				}
			}
			j++;
		}
	}
	return (0);
}
void	error_msg(int fd, int err_num, t_map *map_info, int i)
{
	while (i)
	{
		free(map_info->map[i]);
		i--;
	}
	free(map_info->map);
	if (err_num == 1)
		error(fd, "Must be surrounded with walls\n");
	if (err_num == 2)
		error(fd, "There's other things than exit, collective and players position\n");
	if (err_num == 3)
		error(fd, "There's no collectives!\n");
	if (err_num == 4)
		error(fd, "There's no exit!\n");
	if (err_num == 5)
		error(fd, "There's more than 1 players position\n");
	if (err_num == 6)
		error(fd, "There's no players position\n");
}
void free_(char **arr, int i)
{
	while (i)
	{
		free(arr[i]);
		i--;
	}
	free(arr);
}
void init_comp(t_comp *comp)
{
    comp->coll_cnt = 0;
    comp->exit_cnt = 0;
    comp->play_cnt = 0;
	comp->pl_posx = -1;
	comp->pl_posy = -1;
	comp->pol_cnt = 0;
}
void get_map(int fd, t_map *map_info)
{
	int i;
	int res;
	int rowcount;
	int tmp_rowcount;
	t_comp comp;
	
	i = 0;
	rowcount = map_info->rows_count;
	tmp_rowcount = map_info->rows_count;
	init_comp(&comp);
	while (tmp_rowcount)
	{
		if (!(map_info->map[i] = malloc(sizeof(char) * map_info->rows_count)))
			error(fd, "malloc error\n");
		get_next_line(fd, &map_info->map[i]);
		if ((res = check_map(i, map_info->rows_count, map_info->row_length, map_info->map[i], &comp)) != 0)
			error_msg(fd, res, map_info, i);
		i++;
		tmp_rowcount--;
	}
	if (comp.exit_cnt == 0)
		error_msg(fd, 4, map_info, i - 1);
	if (comp.coll_cnt == 0)
		error_msg(fd, 3, map_info, i - 1);
	if (comp.play_cnt == 0)
		error_msg(fd, 6, map_info, i - 1);
	if (comp.play_cnt > 1)
		error_msg(fd, 5, map_info, i - 1);
	map_info->map[i] = NULL;
	map_info->ply_pos.x = comp.pl_posx;
	map_info->ply_pos.y = comp.pl_posy;
	map_info->collec_count = comp.coll_cnt;
	map_info->pol_cnt = comp.pol_cnt;
}