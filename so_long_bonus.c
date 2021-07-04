/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narakely <narakely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 13:39:19 by narakely          #+#    #+#             */
/*   Updated: 2021/06/30 13:12:03 by narakely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"
#include "stdio.h"
void  my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}
unsigned	int	get_pixel(t_data *data, int x, int y)
{
	unsigned int	color;
	char			*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	color = *(unsigned int*)dst;
	return (color);
}
void	draw_walls(t_map *map_info, t_mlx *tmp)
{
	int i;
	
	i = 0;
	while (i < map_info->rows_count)
	{
		int j = 0;
		while (j < map_info->row_length)
		{
			if (map_info->map[i][j] == '1')
			{
				map_info->img_w.img = mlx_xpm_file_to_image(tmp->mlx, "walls.xpm", &tmp->img_width, &tmp->img_height);
				map_info->img_w.addr = mlx_get_data_addr(map_info->img_w.img, &map_info->img_w.bits_per_pixel, &tmp->img.line_length, &tmp->img.endian);
				mlx_put_image_to_window(tmp->mlx, tmp->mlx_win, map_info->img_w.img, j + 71 * j, i + 71 * i);
			}
			if (map_info->map[i][j] == 'P')
			{
				map_info->img_p.img = mlx_xpm_file_to_image(tmp->mlx, "player1.xpm", &tmp->img_width, &tmp->img_height);
				tmp->img.addr = mlx_get_data_addr(map_info->img_p.img, &tmp->img.bits_per_pixel, &tmp->img.line_length, &tmp->img.endian);
				mlx_put_image_to_window(tmp->mlx, tmp->mlx_win, map_info->img_p.img, j + 71 * j, i + 71 * i);
			}
			if (map_info->map[i][j] == 'C')
			{
				map_info->img_c.img= mlx_xpm_file_to_image(tmp->mlx, "money.xpm", &tmp->img_width, &tmp->img_height);
				tmp->img.addr = mlx_get_data_addr(map_info->img_c.img, &tmp->img.bits_per_pixel, &tmp->img.line_length, &tmp->img.endian);
				mlx_put_image_to_window(tmp->mlx, tmp->mlx_win, map_info->img_c.img, j + 71 * j, i + 71 * i);
			}
			if (map_info->map[i][j] == 'E')
			{
				map_info->img_e.img = mlx_xpm_file_to_image(tmp->mlx, "safe.xpm", &tmp->img_width, &tmp->img_height);
				tmp->img.addr = mlx_get_data_addr(map_info->img_e.img, &tmp->img.bits_per_pixel, &tmp->img.line_length, &tmp->img.endian);
				mlx_put_image_to_window(tmp->mlx, tmp->mlx_win, map_info->img_e.img, j + 71 * j, i + 71 * i);
			}
            if (map_info->map[i][j] == 'M')
			{
				map_info->img_m.img = mlx_xpm_file_to_image(tmp->mlx, "police.xpm", &tmp->img_width, &tmp->img_height);
				tmp->img.addr = mlx_get_data_addr(map_info->img_m.img, &tmp->img.bits_per_pixel, &tmp->img.line_length, &tmp->img.endian);
				mlx_put_image_to_window(tmp->mlx, tmp->mlx_win, map_info->img_m.img, j + 71 * j, i + 71 * i);
			}
			j++;
		}
		i++;
	}
}
void draw_background(t_mlx *tmp, int len, int wid)
{
	tmp->img.img = mlx_new_image(tmp->mlx, len, wid);
	char *buffer = mlx_get_data_addr(tmp->img.img, &tmp->img.bits_per_pixel, &tmp->img.line_length, &tmp->img.endian);
	int color = 0x396056;
	if (tmp->img.bits_per_pixel != 32)
    	color = mlx_get_color_value(tmp->mlx, color);
	for(int y = 0; y < wid; ++y)
	for(int x = 0; x < len; ++x)
	{
		int pixel = (y * tmp->img.line_length) + (x * 4);

		if (tmp->img.endian == 1)
		{
			buffer[pixel + 0] = (color >> 24);
			buffer[pixel + 1] = (color >> 16) & 0xFF;
			buffer[pixel + 2] = (color >> 8) & 0xFF;
			buffer[pixel + 3] = (color) & 0xFF;
		}
		else if (tmp->img.endian == 0)
		{
			buffer[pixel + 0] = (color) & 0xFF;
			buffer[pixel + 1] = (color >> 8) & 0xFF;
			buffer[pixel + 2] = (color >> 16) & 0xFF;
			buffer[pixel + 3] = (color >> 24);
		}
	}
	mlx_put_image_to_window(tmp->mlx, tmp->mlx_win, tmp->img.img, 0, 0);
}
void free__(t_mlx *tmp)
{
	int i;

	i = 0;
	while (tmp->map_info.map)
	{
		free(tmp->map_info.map[i]);
		i++;
	}
	free(tmp->map_info.map);
}
void move_left(t_map *map_info, int *mv_cnt, t_mlx *tmp)
{
	if (map_info->map[map_info->ply_pos.y][map_info->ply_pos.x - 1] != '1')
	{
        if (map_info->map[map_info->ply_pos.y][map_info->ply_pos.x - 1] == 'M')
        {
                ft_putstr_fd("You lost the game!\n", 1);
				map_info->map[map_info->ply_pos.y][map_info->ply_pos.x] = '0';
				mlx_destroy_image(tmp->mlx, tmp->map_info.img_c.img);
				mlx_destroy_image(tmp->mlx, tmp->map_info.img_e.img);
				mlx_destroy_image(tmp->mlx, tmp->map_info.img_w.img);
				mlx_destroy_image(tmp->mlx, tmp->map_info.img_p.img);
				if (tmp->map_info.pol_cnt != 0)
    				mlx_destroy_image(tmp->mlx, tmp->map_info.img_m.img);
				mlx_destroy_window(tmp->mlx, tmp->mlx_win);
				close(tmp->fd);
				exit(1);
        }
		if (map_info->map[map_info->ply_pos.y][map_info->ply_pos.x - 1] == 'E')
		{
			if (map_info->collec_count != 0)
				ft_putstr_fd("You must collect all collectibles!\n", 1);
			else {
				ft_putstr_fd("GAME OVER!\n", 1);
				map_info->map[map_info->ply_pos.y][map_info->ply_pos.x] = '0';
				mlx_destroy_image(tmp->mlx, tmp->map_info.img_c.img);
				mlx_destroy_image(tmp->mlx, tmp->map_info.img_e.img);
				mlx_destroy_image(tmp->mlx, tmp->map_info.img_w.img);
				mlx_destroy_image(tmp->mlx, tmp->map_info.img_p.img);
              	if (tmp->map_info.pol_cnt != 0)
    				mlx_destroy_image(tmp->mlx, tmp->map_info.img_m.img);
				mlx_destroy_window(tmp->mlx, tmp->mlx_win);
				close(tmp->fd);
				exit(1);
			}
		}
		else {
			if (map_info->map[map_info->ply_pos.y][map_info->ply_pos.x - 1] == 'C')
				map_info->collec_count--;
			map_info->map[map_info->ply_pos.y][map_info->ply_pos.x - 1] = 'P';
			map_info->map[map_info->ply_pos.y][map_info->ply_pos.x] = '0';
			map_info->ply_pos.x = map_info->ply_pos.x - 1;
			(*mv_cnt)++;
		}
	}
}
void move_right(t_map *map_info, int *mv_cnt, t_mlx *tmp)
{
	if (map_info->map[map_info->ply_pos.y][map_info->ply_pos.x + 1] != '1')
	{
        if (map_info->map[map_info->ply_pos.y][map_info->ply_pos.x + 1] == 'M')
        {
                ft_putstr_fd("You lost the game!\n", 1);
				map_info->map[map_info->ply_pos.y][map_info->ply_pos.x] = '0';
				mlx_destroy_image(tmp->mlx, tmp->map_info.img_c.img);
				mlx_destroy_image(tmp->mlx, tmp->map_info.img_e.img);
				mlx_destroy_image(tmp->mlx, tmp->map_info.img_w.img);
				mlx_destroy_image(tmp->mlx, tmp->map_info.img_p.img);
				if (tmp->map_info.pol_cnt != 0)
    				mlx_destroy_image(tmp->mlx, tmp->map_info.img_m.img);
				mlx_destroy_window(tmp->mlx, tmp->mlx_win);
				close(tmp->fd);
				exit(1);
        }
		if (map_info->map[map_info->ply_pos.y][map_info->ply_pos.x + 1] == 'E')
		{
			if (map_info->collec_count != 0)
				ft_putstr_fd("You must collect all collectibles!\n", 1);
			else {
				ft_putstr_fd("GAME OVER!\n", 1);
				map_info->map[map_info->ply_pos.y][map_info->ply_pos.x] = '0';
				mlx_destroy_image(tmp->mlx, tmp->map_info.img_c.img);
				mlx_destroy_image(tmp->mlx, tmp->map_info.img_e.img);
				mlx_destroy_image(tmp->mlx, tmp->map_info.img_w.img);
				mlx_destroy_image(tmp->mlx, tmp->map_info.img_p.img);
                if (tmp->map_info.pol_cnt != 0)
    				mlx_destroy_image(tmp->mlx, tmp->map_info.img_m.img);
				mlx_destroy_window(tmp->mlx, tmp->mlx_win);
				close(tmp->fd);
				exit(1);
			}
		}
		else {
			if (map_info->map[map_info->ply_pos.y][map_info->ply_pos.x + 1] == 'C')
				map_info->collec_count--;
			map_info->map[map_info->ply_pos.y][map_info->ply_pos.x + 1] = 'P';
			map_info->map[map_info->ply_pos.y][map_info->ply_pos.x] = '0';
			map_info->ply_pos.x = map_info->ply_pos.x + 1;
			(*mv_cnt)++;
		}
	}
}
void move_up(t_map *map_info, int *mv_cnt, t_mlx *tmp)
{
	if (map_info->map[map_info->ply_pos.y + 1][map_info->ply_pos.x] != '1')
	{
        if (map_info->map[map_info->ply_pos.y + 1][map_info->ply_pos.x] == 'M')
        {
                ft_putstr_fd("You lost the game!\n", 1);
				map_info->map[map_info->ply_pos.y][map_info->ply_pos.x] = '0';
				mlx_destroy_image(tmp->mlx, tmp->map_info.img_c.img);
				mlx_destroy_image(tmp->mlx, tmp->map_info.img_e.img);
				mlx_destroy_image(tmp->mlx, tmp->map_info.img_w.img);
				mlx_destroy_image(tmp->mlx, tmp->map_info.img_p.img);
                if (tmp->map_info.pol_cnt != 0)
    				mlx_destroy_image(tmp->mlx, tmp->map_info.img_m.img);
				mlx_destroy_window(tmp->mlx, tmp->mlx_win);
				close(tmp->fd);
				exit(1);
        }
		if (map_info->map[map_info->ply_pos.y + 1][map_info->ply_pos.x] == 'E')
		{
			if (map_info->collec_count != 0)
				ft_putstr_fd("You must collect all collectibles!\n", 1);
			else {
				ft_putstr_fd("GAME OVER!\n", 1);
				map_info->map[map_info->ply_pos.y][map_info->ply_pos.x] = '0';
				mlx_destroy_image(tmp->mlx, tmp->map_info.img_c.img);
				mlx_destroy_image(tmp->mlx, tmp->map_info.img_e.img);
				mlx_destroy_image(tmp->mlx, tmp->map_info.img_w.img);
				mlx_destroy_image(tmp->mlx, tmp->map_info.img_p.img);
				if (tmp->map_info.pol_cnt != 0)
    				mlx_destroy_image(tmp->mlx, tmp->map_info.img_m.img);
				mlx_destroy_window(tmp->mlx, tmp->mlx_win);
				close(tmp->fd);
				exit(1);
			}
		}
		else {
			if (map_info->map[map_info->ply_pos.y + 1][map_info->ply_pos.x] == 'C')
				map_info->collec_count--;
			map_info->map[map_info->ply_pos.y + 1][map_info->ply_pos.x] = 'P';
			map_info->map[map_info->ply_pos.y][map_info->ply_pos.x] = '0';
			map_info->ply_pos.y = map_info->ply_pos.y + 1;
			(*mv_cnt)++;
		}
	}
}
void move_down(t_map *map_info, int *mv_cnt, t_mlx *tmp)
{
	if (map_info->map[map_info->ply_pos.y - 1][map_info->ply_pos.x] != '1')
	{
        if (map_info->map[map_info->ply_pos.y - 1][map_info->ply_pos.x] == 'M')
        {
                ft_putstr_fd("You lost the game!\n", 1);
				map_info->map[map_info->ply_pos.y][map_info->ply_pos.x] = '0';
				mlx_destroy_image(tmp->mlx, tmp->map_info.img_c.img);
				mlx_destroy_image(tmp->mlx, tmp->map_info.img_e.img);
				mlx_destroy_image(tmp->mlx, tmp->map_info.img_w.img);
				mlx_destroy_image(tmp->mlx, tmp->map_info.img_p.img);
                if (tmp->map_info.pol_cnt != 0)
    				mlx_destroy_image(tmp->mlx, tmp->map_info.img_m.img);
				mlx_destroy_window(tmp->mlx, tmp->mlx_win);
				close(tmp->fd);
				exit(1);
        }
		if (map_info->map[map_info->ply_pos.y - 1][map_info->ply_pos.x] == 'E')
		{
			if (map_info->collec_count != 0)
			{
				ft_putstr_fd("You must collect all collectibles!\n", 1);
			}
			else {
				ft_putstr_fd("GAME OVER!\n", 1);
				map_info->map[map_info->ply_pos.y][map_info->ply_pos.x] = '0';
				mlx_destroy_image(tmp->mlx, tmp->map_info.img_c.img);
				mlx_destroy_image(tmp->mlx, tmp->map_info.img_e.img);
				mlx_destroy_image(tmp->mlx, tmp->map_info.img_w.img);
				mlx_destroy_image(tmp->mlx, tmp->map_info.img_p.img);
				if (tmp->map_info.pol_cnt != 0)
    				mlx_destroy_image(tmp->mlx, tmp->map_info.img_m.img);
				mlx_destroy_window(tmp->mlx, tmp->mlx_win);
				close(tmp->fd);
				exit(1);
			}
		}
		else {
			if (map_info->map[map_info->ply_pos.y - 1][map_info->ply_pos.x] == 'C')
				map_info->collec_count--;
			map_info->map[map_info->ply_pos.y - 1][map_info->ply_pos.x] = 'P';
			map_info->map[map_info->ply_pos.y][map_info->ply_pos.x] = '0';
			map_info->ply_pos.y = map_info->ply_pos.y - 1;
			(*mv_cnt)++;
		}
	}
}
char *number_to_string(int num)
{
	int len;
	int temp;
	char *str;
	int i;

	len = 0;
	i = 0;
	temp = num;
	while (temp)
	{
		len++;
		temp = temp / 10;
	}
	if (!(str = malloc((len + 1) * sizeof(char))))
		return (NULL);
	while (len)
	{
		str[len - 1] = num % 10 + 48;
		len--;
		num = num / 10;
	}
	return (str);
}
int	keyhook(int keycode, t_mlx *tmp)
{
	char* cnt;
	mlx_destroy_image(tmp->mlx, tmp->img.img);
	if (keycode == 53)
	{
		mlx_destroy_window(tmp->mlx, tmp->mlx_win);
		exit(1);
	}
	if (keycode == KEY_A)
		move_left(&tmp->map_info, &tmp->mov_cnt, tmp);
	if (keycode == KEY_D)
		move_right(&tmp->map_info, &tmp->mov_cnt, tmp);
	if (keycode == KEY_W)
		move_down(&tmp->map_info, &tmp->mov_cnt, tmp);
	if (keycode == KEY_S)
		move_up(&tmp->map_info, &tmp->mov_cnt, tmp);
	int color = 0x000000;
	draw_background(tmp, 71 * tmp->map_info.row_length, 71 * tmp->map_info.rows_count);
	draw_walls(&tmp->map_info, tmp);
	if (!(cnt = number_to_string(tmp->mov_cnt)))
	{
		mlx_destroy_image(tmp->mlx, tmp->img.img);
		mlx_destroy_image(tmp->mlx, tmp->map_info.img_c.img);
		mlx_destroy_image(tmp->mlx, tmp->map_info.img_e.img);
		mlx_destroy_image(tmp->mlx, tmp->map_info.img_w.img);
		mlx_destroy_image(tmp->mlx, tmp->map_info.img_p.img);
		if (tmp->map_info.pol_cnt != 0)
    		mlx_destroy_image(tmp->mlx, tmp->map_info.img_m.img);
		free__(tmp);
		error(tmp->fd, "Malloc error\n");
	}
	mlx_string_put(tmp->mlx, tmp->mlx_win, 0, 0, color, "Movements count");
	mlx_string_put(tmp->mlx, tmp->mlx_win, 160, 0, color, cnt);
	free(cnt);
	return (0);
}
int ft_close(t_mlx *tmp)
{
	int i;

	i = 0;
	while (tmp->map_info.map[i] != NULL)
	{
		free(tmp->map_info.map[i]);
		i++;
	}
	free(tmp->map_info.map[i]);
	mlx_destroy_image(tmp->mlx, tmp->img.img);
	mlx_destroy_image(tmp->mlx, tmp->map_info.img_c.img);
	mlx_destroy_image(tmp->mlx, tmp->map_info.img_e.img);
	mlx_destroy_image(tmp->mlx, tmp->map_info.img_w.img);
	mlx_destroy_image(tmp->mlx, tmp->map_info.img_p.img);
	if (tmp->map_info.pol_cnt != 0)
    	mlx_destroy_image(tmp->mlx, tmp->map_info.img_m.img);
	mlx_destroy_window(tmp->mlx, tmp->mlx_win);
	exit (0);
	return (0);
}
int namecheck(char *str)
{
	int i;
	int len;
	char *s;
	
	i = 0;
	s = "reb.";
	len = ft_strlen(str) - 1;
	
	while (i < 4)
	{
		if (str[len] != s[i])
			return (0);
		i++;
		len--;
	}
	return (1);
}
int	main(int argc, char** argv)
{
	t_mlx tmp;
	int j = 0;
	if (argc == 2)
	{
		tmp.mov_cnt = 0;
		if (!namecheck(argv[1]))
		{
			ft_putstr_fd("ERROR: Files extension must be .ber\n", 1);
			return (0);
		}
		if (!(tmp.fd = open(argv[1], O_RDONLY)))
			error(tmp.fd, "file open error\n");
		tmp.map_info.rows_count = get_count(tmp.fd, &(tmp.map_info.row_length));
		if (tmp.map_info.rows_count == -1)
			error(tmp.fd, "Map must be rectangular\n");
		if (!(tmp.map_info.map = (char **)malloc(sizeof(char*) * (tmp.map_info.rows_count + 1))))
			error(tmp.fd, "Malloc error\n");
		close(tmp.fd);
		if (!(tmp.fd = open(argv[1], O_RDONLY)))
			error(tmp.fd, "File open error\n");
		get_map(tmp.fd, &tmp.map_info);
		tmp.mlx = mlx_init();
		tmp.mlx_win = mlx_new_window(tmp.mlx, 71 * tmp.map_info.row_length, 71 * tmp.map_info.rows_count, "So Long!");
		draw_background(&tmp, 71 * tmp.map_info.row_length, 71 * tmp.map_info.rows_count);
		draw_walls(&tmp.map_info, &tmp);
		mlx_string_put(tmp.mlx, tmp.mlx_win, 0, 0, 0x00000, "Movements count 0");
		mlx_hook(tmp.mlx_win, 2, 1L<<0, keyhook, &tmp);
		mlx_hook(tmp.mlx_win, 17, 0, ft_close, &tmp);
		mlx_loop(tmp.mlx);
		while (tmp.map_info.map[j] != NULL)
		{
			free(tmp.map_info.map[j]);
			j++;
		}
		free(tmp.map_info.map);
		close(tmp.fd);
	}
	ft_putstr_fd("ERROR: There's no argument\n", 1);
	return (0);
}