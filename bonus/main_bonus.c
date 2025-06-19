/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleconst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 13:40:45 by aleconst          #+#    #+#             */
/*   Updated: 2025/06/09 13:40:47 by aleconst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static void	error_checker(t_map *map, t_player *player, int unique_c_count)
{
	if (map->x == map->y)
		err_exit(map, "Error\nMap is not a rectangle", 1);
	if (unique_c_count > 2)
		err_exit(map, "Error\nThere must be only 1 exit and 1 player", 1);
	else if (unique_c_count < 2)
		err_exit(map, "Error\nThere must be at least 1 exit and 1 player", 1);
	if (map->eggs < 1)
		err_exit(map, "Error\nThere must be at least one collectible", 1);
	if (check_enclosed(*map) == 0)
		err_exit(map, "Error\nMap must be surrounded by walls («1»)", 1);
	if (pathfinder(map, player) == 0)
		err_exit(map, "Error\nMap must have reacheable exit/collectibles", 1);
}

static void	file_format(char *name)
{
	char	**parts;
	int		i;

	if (ft_strlen(name) < 5)
		err_exit(NULL, "Error\nMap file format must be .ber", 1);
	parts = ft_split(name, '.');
	if (!parts)
		err_exit(NULL, "Error\nMalloc failed", 1);
	i = 0;
	while (parts[i])
		i++;
	i--;
	if (ft_strncmp(parts[i], "ber", 3) != 0)
	{
		ft_free_wa(parts);
		err_exit(NULL, "Error\nMap file format must be .ber", 1);
	}
	ft_free_wa(parts);
}

void	start_game(char *filename)
{
	t_map		map;
	t_player	player;
	int			map_fd;
	int			unique_c_count;


	map_fd = open(filename, O_RDONLY);
	if (map_fd == -1)
		err_exit(NULL, "Error\nFile doesn't exist or no permissions", 1);
	file_format(filename);
	unique_c_count = 0;
	map = map_extraction(map_fd, &unique_c_count, map);
	close(map_fd);
	player.moves = 0;
	map.filename = filename;
	error_checker(&map, &player, unique_c_count);
	create_window(&map, &player);
	free_map(&map);
}

int	main(int argc, char **argv)
{
	if (argc != 2)
		err_exit(NULL, "Error\nThere must be only 1 argument", 1);
	start_game(argv[1]);
	return (0);
}
