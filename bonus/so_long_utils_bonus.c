
#include "so_long_bonus.h"

void	free_map(t_map *map)
{
	int	y;

	if (!map || !map->cells)
		return ;
	y = 0;
	while (y < map->y)
	{
		free(map->cells[y]);
		y++;
	}
	free(map->cells);
	map->cells = NULL;
	map->x = 0;
	map->y = 0;
}

void	err_exit(t_map *map, char *message, int error_code)
{
	if (message)
	{
		write(2, message, ft_strlen(message));
		write(2, "\n", 1);
	}
	free_map(map);
	exit(error_code);
}

int	get_sprite_index(char tile)
{
	if (tile == '0')
		return (0);
	else if (tile == '1')
		return (1);
	else if (tile == 'P')
		return (2);
	else if (tile == 'C')
		return (3);
	else if (tile == 'E')
		return (4);
	else if (tile == 'X')
		return (6);
	return (-1);
}

void	load_sprites(t_data *data)
{
	int	w;
	int	h;

	data->sprites[0] = mlx_xpm_file_to_image(data->mlx,
			"textures/rock.xpm", &w, &h);
	data->sprites[1] = mlx_xpm_file_to_image(data->mlx,
			"textures/water.xpm", &w, &h);
	data->sprites[2] = mlx_xpm_file_to_image(data->mlx,
			"textures/frog_rock.xpm", &w, &h);
	data->sprites[3] = mlx_xpm_file_to_image(data->mlx,
			"textures/egg_rock.xpm", &w, &h);
	data->sprites[4] = mlx_xpm_file_to_image(data->mlx,
			"textures/exit.xpm", &w, &h);
	data->sprites[5] = mlx_xpm_file_to_image(data->mlx,
			"textures/frog_exit.xpm", &w, &h);
	data->sprites[6] = mlx_xpm_file_to_image(data->mlx,
			"textures/snake.xpm", &w, &h);
}

void	update_camera(t_data *data, int dx, int dy)
{
	int	max_x;
	int	max_y;

	max_x = data->map->x - VIEW_WIDTH;
	max_y = data->map->y - VIEW_HEIGHT;
	if (max_x < 0)
		data->camera_x = 0;
	else if (dx != 0)
	{
		if (data->player->x - data->camera_x < 2 && data->camera_x > 0)
			data->camera_x--;
		else if (data->player->x - data->camera_x >= VIEW_WIDTH - 2
			&& data->camera_x < max_x)
			data->camera_x++;
	}
	if (max_y < 0)
		data->camera_y = 0;
	else if (dy != 0)
	{
		if (data->player->y - data->camera_y < 2 && data->camera_y > 0)
			data->camera_y--;
		else if (data->player->y - data->camera_y >= VIEW_HEIGHT - 2
			&& data->camera_y < max_y)
			data->camera_y++;
	}
}
