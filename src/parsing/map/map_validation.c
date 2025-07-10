/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonimo <antonimo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 11:44:48 by antonimo          #+#    #+#             */
/*   Updated: 2025/07/10 13:21:33 by antonimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	validate_complete_map(t_game *cub3d)
{
	if (!cub3d->map.map || !cub3d->map.map[0])
	{
		write_error("Map is empty or not defined.\n");
		return (false);
	}
	if (!find_and_validate_player(cub3d))
		return (false);
	if (!validate_map_enclosed(cub3d))
		return (false);
	return (true);
}

static void	store_player(t_game *cub3d, int x, int y)
{
	if (cub3d->map.map[x][y] == NORTH)
		cub3d->player.dir = NORTH;
	else if (cub3d->map.map[x][y] == SOUTH)
		cub3d->player.dir = SOUTH;
	else if (cub3d->map.map[x][y] == WEST)
		cub3d->player.dir = WEST;
	else if (cub3d->map.map[x][y] == EAST)
		cub3d->player.dir = EAST;
}

static bool	validate_one_player(t_game *cub3d, int x, int y)
{
	while (cub3d->map.map[x][y])
	{
		if (cub3d->map.map[x][y] == NORTH || cub3d->map.map[x][y] == SOUTH
			|| cub3d->map.map[x][y] == EAST || cub3d->map.map[x][y] == WEST)
		{
			if (!cub3d->player.x && !cub3d->player.y)
			{
				cub3d->player.x = x;
				cub3d->player.y = y;
				store_player(cub3d, x, y);
			}
			else
			{
				write_error("Map contains more than one player");
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
	if (!cub3d->player.x && !cub3d->player.y)
	{
		write_error("No player found in map");
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
	result = validate_flood_fill(cub3d->player.x,
			cub3d->player.y, map_copy);
	free_matrix(map_copy);
	if (!result)
		write_error("Map is not properly enclosed by walls");
	return (result);
}
