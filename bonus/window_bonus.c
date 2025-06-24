/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleconst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 13:41:26 by aleconst          #+#    #+#             */
/*   Updated: 2025/06/09 13:41:33 by aleconst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static int	close_window(t_data *data, int lose)
{
	int	i;

	i = 0;
	while (i < 7)
	{
		if (data->sprites[i])
			mlx_destroy_image(data->mlx, data->sprites[i]);
		i++;
	}
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	free_map(data->map);
	if (lose == 1)
	{
		ft_printf("YOU DIED!\n");
		start_game(data->map->filename);
	}
	exit(0);
	return (0);
}

static void	draw_frog(t_data *data)
{
	int	frog_type;
	int	screen_x;
	int	screen_y;

	frog_type = 2;
	if (data->map->cells[data->player->y][data->player->x].type == 'E')
		frog_type = 5;
	screen_x = (data->player->x - data->camera_x) * SPRITE_SIZE;
	screen_y = (data->player->y - data->camera_y) * SPRITE_SIZE;
	mlx_put_image_to_window(data->mlx, data->win,
		data->sprites[frog_type], screen_x, screen_y);
	draw_move_counter(data);
}

static void	draw_map(t_data *data)
{
	int		x;
	int		y;
	char	tile;
	int		sprite;

	y = -1;
	while (++y < VIEW_HEIGHT)
	{
		x = -1;
		while (++x < VIEW_WIDTH)
		{
			if (y + data->camera_y >= data->map->y
				|| x + data->camera_x >= data->map->x)
				continue ;
			tile = data->map->cells[y + data->camera_y][x + data->camera_x]
				.type;
			mlx_put_image_to_window(data->mlx, data->win,
				data->sprites[0], x * SPRITE_SIZE, y * SPRITE_SIZE);
			sprite = get_sprite_index(tile);
			if (sprite != -1 && tile != '0' && tile != 'P')
				mlx_put_image_to_window(data->mlx, data->win,
					data->sprites[sprite], x * SPRITE_SIZE, y * SPRITE_SIZE);
		}
	}
	draw_frog(data);
}

static int	key_hook(int keycode, t_data *data)
{
	int	moved;

	moved = 0;
	if (keycode == ESC)
		close_window(data, 0);
	if (keycode == W)
		moved = move_frog(data, 1, 0);
	else if (keycode == A)
		moved = move_frog(data, 0, 1);
	else if (keycode == S)
		moved = move_frog(data, -1, 0);
	else if (keycode == D)
		moved = move_frog(data, 0, -1);
	if (moved == 1 || moved == 2)
		draw_map(data);
	if (moved == 2)
	{
		ft_printf("************\n* YOU WIN! *\n************\n");
		close_window(data, 0);
	}
	if (moved == 3)
	{
		close_window(data, 1);
	}
	return (0);
}

void	create_window(t_map *map, t_player *player)
{
	t_data		data;
	int			i;

	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, WINDOW_WIDTH,
			WINDOW_HEIGHT, "Sewer frog");
	data.map = map;
	data.player = player;
	i = -1;
	while (++i < 7)
		data.sprites[i] = NULL;
	data.camera_x = 0;
	data.camera_y = 0;
	if (load_sprites(&data) == 0)
	{
		write(2, "Error\nMissing/can't open sprites\n", 33);
		close_window(&data, 0);
	}
	center_camera_on_player(&data);
	draw_map(&data);
	mlx_key_hook(data.win, key_hook, &data);
	mlx_hook(data.win, 17, 0, close_window, &data);
	mlx_loop(data.mlx);
}
