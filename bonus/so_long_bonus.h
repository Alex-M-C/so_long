#ifndef SO_LONG_H
# define SO_LONG_H

# include "../minilibx/mlx.h"
# include "../libft/libft.h"
# include <fcntl.h>
# include <unistd.h>

# define ESC 65307
# define W 119
# define A 97
# define S 115
# define D 100
# define SPRITE_SIZE 128
# define WINDOW_WIDTH 1660
# define WINDOW_HEIGHT 640
# define VIEW_HEIGHT 5
# define VIEW_WIDTH 13

typedef struct s_player
{
	int	x;
	int	y;
	int	moves;
}	t_player;

typedef struct s_cell
{
	int		visited;
	char	type;
}	t_cell;

typedef struct s_map
{
	t_cell	**cells;
	int		x;
	int		y;
	int		eggs;
	char	*filename;
}	t_map;

typedef struct s_img_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_img_data;

typedef struct s_data
{
	void		*mlx;
	void		*win;
	t_img_data	*img;
	void		*sprites[7];
	t_map		*map;
	t_player	*player;
	int			camera_x;
	int			camera_y;
}	t_data;

void	start_game(char *filename);

t_map	map_extraction(int map_fd, int *unique_c_count, t_map map);

int		check_enclosed(t_map map);

int		pathfinder(t_map *map, t_player *player);

void	create_window(t_map *map, t_player *player);

int		get_sprite_index(char tile);

int		move_frog(t_data *data, int oy, int ox);

void	load_sprites(t_data *data);

void	update_camera(t_data *data, int dx, int dy);

void 	center_camera_on_player(t_data *data);

void	free_map(t_map *map);

void	err_exit(t_map *map, char *message, int error_code);

#endif