/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleconst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 13:41:03 by aleconst          #+#    #+#             */
/*   Updated: 2025/06/09 13:41:05 by aleconst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/*
Checks if all the lines are the same length and establish the MAP.X length for
the current line.
*/
static void	map_x_len(char **line, t_map *map)
{
	int	line_len;

	line_len = ft_strlen(*line);
	if ((*line)[line_len - 1] == '\n')
		line_len--;
	if (map->y == 0)
		map->x = line_len;
	else if (line_len != map->x)
	{
		free(*line);
		err_exit(map, "Error\nMap is not a rectangle", 1);
	}
}

/*
Increases the number of rows of the map by 1 using malloc(3)
to allocate space for the new row.
*/
static t_cell	**grow_row(t_cell **old_cells, int old_count)
{
	t_cell	**new_cells;
	int		i;

	new_cells = malloc(sizeof(t_cell *) * (old_count + 1));
	if (!new_cells)
		return (NULL);
	i = 0;
	while (i < old_count)
	{
		new_cells[i] = old_cells[i];
		i++;
	}
	free(old_cells);
	new_cells[old_count] = NULL;
	return (new_cells);
}

/*
Puts each character from the LINE recieved into the CELLS from MAP
*/
static void	assign_cells(char **line, t_map *map, int *unique_c_count)
{
	int	x;

	x = -1;
	while ((*line)[++x] && (*line)[x] != '\n' && x < map->x)
	{
		if ((*line)[x] == 'E' || (*line)[x] == 'P')
			(*unique_c_count)++;
		else if ((*line)[x] == 'C')
			map->eggs++;
		else if ((*line)[x] != '1' && (*line)[x] != '0')
		{
			free(*line);
			free(map->cells[map->y]);
			err_exit(map, "Error\nForbbiden characters found", 1);
		}
		map->cells[map->y][x].type = (*line)[x];
		map->cells[map->y][x].visited = 0;
	}
}

/*
Extracts all the info and/or characters from the .ber file and builds the map.
*/
void	map_extraction(int map_fd, int *unique_c_count, t_map *map)
{
	char	*line;

	map->cells = NULL;
	map->eggs = 0;
	map->x = 0;
	map->y = 0;
	line = get_next_line(map_fd);
	while (line)
	{
		map_x_len(&line, map);
		map->cells = grow_row(map->cells, map->y);
		if (!map->cells)
			exit(1);
		map->cells[map->y] = malloc(sizeof(t_cell) * map->x);
		if (!map->cells[map->y])
		{
			free(line);
			err_exit(map, "Error\nMalloc failed", 1);
		}
		assign_cells(&line, map, unique_c_count);
		map->y++;
		free(line);
		line = get_next_line(map_fd);
	}
}

/*
Checks if the map is surrounded by walls.
@returns 1 if is enclosed, 0 if it isn't.
*/
int	check_enclosed(t_map map)
{
	int	x;
	int	y;

	y = 0;
	while (y < map.y)
	{
		if (y == 0 || y == map.y - 1)
		{
			x = 0;
			while (x < map.x)
			{
				if (map.cells[y][x].type != '1')
					return (0);
				x++;
			}
		}
		else if (map.cells[y][0].type != '1'
				|| map.cells[y][map.x - 1].type != '1')
		{
			return (0);
		}
		y++;
	}
	return (1);
}
