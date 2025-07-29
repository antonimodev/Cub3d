/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarian <frmarian@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 13:24:51 by antonimo          #+#    #+#             */
/*   Updated: 2025/07/29 12:11:12 by frmarian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	collision(t_coords ray, t_map *map)
{
	int	x;
	int	y;

	x = (int)(ray.x / BLOCK);
	y = (int)(ray.y / BLOCK);
	if (x < 0 || y < 0 || y >= map->map_height)
		return (true);
	if (x >= (int)ft_strlen(map->map[y]))
		return (true);
	return (map->map[y][x] == WALL);
}

static bool	player_collision(t_coords new_pos, t_map *map, float margin)
{
	t_coords	check_points[4];
	int			i;

	check_points[0].y = new_pos.y - margin;
	check_points[0].x = new_pos.x - margin;
	check_points[1].y = new_pos.y - margin;
	check_points[1].x = new_pos.x + margin;
	check_points[2].y = new_pos.y + margin;
	check_points[2].x = new_pos.x - margin;
	check_points[3].y = new_pos.y + margin;
	check_points[3].x = new_pos.x + margin;
	i = 0;
	while (i < 4)
	{
		if (collision(check_points[i], map))
			return (true);
		i++;
	}
	return (false);
}

void	move_with_collision(t_game *cub3d, float delta_x, float delta_y)
{
	t_coords	new_pos;
	float		margin;

	margin = BLOCK / 6;
	new_pos.x = cub3d->player.coords.x + delta_x;
	new_pos.y = cub3d->player.coords.y;
	if (!player_collision(new_pos, &cub3d->map, margin))
		cub3d->player.coords.x = new_pos.x;
	new_pos.x = cub3d->player.coords.x;
	new_pos.y = cub3d->player.coords.y + delta_y;
	if (!player_collision(new_pos, &cub3d->map, margin))
		cub3d->player.coords.y = new_pos.y;
}
