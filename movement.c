/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleconst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 13:15:54 by aleconst          #+#    #+#             */
/*   Updated: 2025/06/19 13:15:57 by aleconst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	move_frog(t_data *data, int oy, int ox)
{
	if (data->player->y - oy < 0 || data->player->y - oy >= data->map->y
		|| data->map->cells[data->player->y - oy][data->player->x - ox]
		.type == '1'
		|| data->player->x - ox < 0 || data->player->x - ox >= data->map->x)
		return (0);
	if (data->map->cells[data->player->y - oy][data->player->x - ox]
		.type == 'C')
	{
		data->map->eggs--;
		data->map->cells[data->player->y - oy][data->player->x - ox].type = '0';
	}
	if (data->map->cells[data->player->y - oy][data->player->x - ox].type == 'E'
		&& data->map->eggs == 0)
	{
		data->player->moves++;
		return (2);
	}
	data->player->y -= oy;
	data->player->x -= ox;
	data->player->moves++;
	update_camera(data, ox, oy);
	return (1);
}

void	center_camera_on_player(t_data *data)
{
	int	half_w;
	int	half_h;
	int	max_x;
	int	max_y;

	half_w = VIEW_WIDTH / 2;
	half_h = VIEW_HEIGHT / 2;
	max_x = data->map->x - VIEW_WIDTH;
	max_y = data->map->y - VIEW_HEIGHT;
	data->camera_x = data->player->x - half_w;
	data->camera_y = data->player->y - half_h;
	if (data->camera_x < 0)
		data->camera_x = 0;
	else if (max_x >= 0 && data->camera_x > max_x)
		data->camera_x = max_x;
	if (data->camera_y < 0)
		data->camera_y = 0;
	else if (max_y >= 0 && data->camera_y > max_y)
		data->camera_y = max_y;
}
