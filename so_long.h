#ifndef SO_LONG_H
# define SO_LONG_H

#include "gnl/get_next_line.h"
#include "mlx.h"
#include "fcntl.h"
#include "unistd.h"
// #include "libft/libft.h"

#define KEY_A 0
#define KEY_S 1
#define KEY_D 2
#define KEY_W 13

typedef struct	s_pos
{
	int x;
	int y;
}				t_pos;
typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;
typedef	struct	s_map
{
	char **map;
	int row_length;
	int rows_count;
	int exits_count;
	int collec_count;
	t_pos exits[30];
	t_pos colec[30]; 
	t_pos ply_pos;
	t_data img_p;
	t_data img_c;
	t_data img_e;
	t_data img_w;
}				t_map;
typedef struct	s_mlx
{
	void *mlx;
	void *mlx_win;
	t_data img;
	int		img_width;
	int		img_height;
	t_map map_info;
	int		mov_cnt;
	int fd;
}				t_mlx;
typedef	struct	s_comp
{
	int exit_cnt;
	int play_cnt;
	int coll_cnt;
	int pl_posx;
	int pl_posy;
	/* data */
}				t_comp;
void	ft_putchar_fd(char c, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_putstr_fd(char *s, int fd);
int		ft_strlen(const char *s);
int 	get_count(int fd, int* rows_length);
void 	error(int fd, char *err_msg);
int		exit_collec_count(char line_j, t_comp *comp);
int		check_map(int i, int row_count, int row_length, char *line, t_comp *comp);
void	error_msg(int fd, int err_num, t_map *map_info, int i);
void 	free_(char **arr, int i);
void 	init_comp(t_comp *comp);
void	get_map(int fd, t_map *map_info);
#endif