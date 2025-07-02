#include "cub3d.h"

bool    parsing(char **av, t_game *cub3d)
{
    int     fd;

    fd = open(av[1], O_RDONLY);
    return (parse_line(&fd, cub3d));
}

bool    parse_line(int *fd, t_game *cub3d)
{
	char    *line;

	line = get_next_line(*fd);
	if (!line)
	{
		write_error("Error\nFailed to read the file.\n");
		return (false);
	}
	while (line)
	{
		if (!get_data_from_line(line, cub3d)) // Check line to store data in the game structure
		{
			free(line);
			return (false);
		}
		free(line);
		line = get_next_line(*fd);
	}
	if (!validate_assigned_params(cub3d))
		return (false);
	return (true);
}

bool    get_data_from_line(char *line, t_game *cub3d)
{
	if (!get_texture_path(line, cub3d)) // North, South, West, East texture paths
		return (false); // If texture path is invalid
	if (!get_color(line, cub3d)) // Ceiling + Floor colors
		return (false); // If color is invalid
	if (!get_map_data(line, cub3d)) // Map data
		return (false); // If map data is invalid
	return (true);
}

bool	validate_assigned_params(t_game *cub3d)
{
	if (!cub3d->texture_paths.no || !cub3d->texture_paths.so ||
		!cub3d->texture_paths.ea || !cub3d->texture_paths.we)
	{
		write_error("Error\nMissing texture paths. All four textures (NO, SO, EA, WE) are required\n");
		return (false);
	}
	if (!cub3d->colors.floor_set || !cub3d->colors.ceiling_set)
	{
		write_error("Error\nMissing color definitions. Both Floor (F) and Ceiling (C) colors are required\n");
		return (false);
	}
	if (!validate_complete_map(cub3d))
		return (false);
	return (true);
}

bool	validate_complete_map(t_game *cub3d)
{
	if (!cub3d->map.map || !cub3d->map.map[0])
	{
		write_error("Error\nMap is empty or not defined.\n");
		return (false);
	}
	if (!find_and_validate_player(cub3d))
		return (false); // If player is not found or multiple players are found
	if (!validate_map_enclosed(cub3d))
		return (false); // If walls are not enclosed
	return (true);
}
