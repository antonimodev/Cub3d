#include "cub3d.h"

bool	validate_complete_map(t_game *cub3d)
{
	if (!cub3d->map.map || !cub3d->map.map[0])
	{
		write_error("Error\nMap is empty or not defined.\n");
		return (false);
	}
	if (!find_and_validate_player(cub3d))
		return (false);
	if (!validate_map_enclosed(cub3d))
		return (false);
	return (true);
}

static bool	validate_one_player(t_game *cub3d, int x, int y)
{
	while (cub3d->map.map[x][y])
	{
		if (cub3d->map.map[x][y] == 'N' || cub3d->map.map[x][y] == 'S'
			|| cub3d->map.map[x][y] == 'E' || cub3d->map.map[x][y] == 'W')
		{
			if (!cub3d->player_pos.x && !cub3d->player_pos.y)
			{
				cub3d->player_pos.x = x;
				cub3d->player_pos.y = y;
			}
			else
			{
				write_error("Error\nMap contains more than one player");
				return (false);
			}
		}
		y++;
	}
	return (true);
}

bool	find_and_validate_player(t_game *cub3d)
{
	int	x_pos;

	x_pos = 0;
	while (cub3d->map.map[x_pos])
	{
		if (!validate_one_player(cub3d, x_pos, 0))
			return (false);
		x_pos++;
	}
	if (!cub3d->player_pos.x && !cub3d->player_pos.y)
	{
		write_error("Error\nNo player found in map");
		return (false);
	}
	return (true);
}

bool	validate_map_enclosed(t_game *cub3d)
{
	char	**map_copy;
	bool	result;

	map_copy = matrix_cpy(cub3d->map.map, 0);
	if (!map_copy)
		return (false);
	
	result = validate_flood_fill(cub3d->player_pos.x, cub3d->player_pos.y, map_copy);
	free_matrix(map_copy);
	
	if (!result)
		write_error("Error\nMap is not properly enclosed by walls");
	
	return (result);
}
