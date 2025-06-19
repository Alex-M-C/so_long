/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_finder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleconst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 13:41:14 by aleconst          #+#    #+#             */
/*   Updated: 2025/06/09 13:41:15 by aleconst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static void	get_starting_pos(t_map map, int *start_x, int *start_y)
{
	*start_y = 0;
	while (*start_y < map.y)
	{
		*start_x = 0;
		while (*start_x < map.x)
		{
			if (map.cells[(*start_y)][(*start_x)].type == 'P')
				return ;
			(*start_x)++;
		}
		(*start_y)++;
	}
}

static void	check_cells(t_map *map, int *ispath, int x, int y)
{
	if (x < 0 || x >= map->x || y < 0 || y >= map->y)
		return ;
	else if (map->cells[y][x].visited == 1 || map->cells[y][x].type == '1')
		return ;
	else if (map->cells[y][x].type == 'C')
		map->eggs--;
	else if (map->cells[y][x].type == 'E')
		*ispath = 1;
	map->cells[y][x].visited = 1;
	check_cells(map, ispath, x - 1, y);
	check_cells(map, ispath, x, y - 1);
	check_cells(map, ispath, x, y + 1);
	check_cells(map, ispath, x + 1, y);
}

/*
Checks if there is a path to the exit of the map
*/
int	pathfinder(t_map *map, t_player *player)
{
	int		temp_eggs;
	int		ispath;

	ispath = 0;
	temp_eggs = map->eggs;
	get_starting_pos(*map, &(player->x), &(player->y));
	check_cells(map, &ispath, player->x, player->y);
	if (ispath == 1 && map->eggs == 0)
	{
		map->eggs = temp_eggs;
		return (1);
	}
	else
		return (0);
}
