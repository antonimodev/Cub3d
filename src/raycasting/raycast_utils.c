/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarian <frmarian@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 13:10:58 by antonimo          #+#    #+#             */
/*   Updated: 2025/07/29 14:16:20 by frmarian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static float	calc_wall_pos(t_coords impact_point, int wall_side)
{
	float	wall_x;
	float	pos_in_block;

	if (wall_side == VERTICAL_HIT)
		pos_in_block = impact_point.y - floor(impact_point.y / BLOCK) * BLOCK;
	else
		pos_in_block = impact_point.x - floor(impact_point.x / BLOCK) * BLOCK;
	wall_x = pos_in_block / BLOCK;
	return (wall_x);
}

int	clamp_texture_coords(int coordinate, int max_value)
{
	if (coordinate < 0)
		return (0);
	if (coordinate >= max_value)
		return (max_value - 1);
	return (coordinate);
}

void	flip_texture(float wall_side, float *wall_x, t_coords ray_dir)
{
	if ((wall_side == VERTICAL_HIT && ray_dir.x < 0)
		|| (wall_side == HORIZONTAL_HIT && ray_dir.y > 0))
		*wall_x = 1.0f - *wall_x;
}

int	get_texture_column(t_image *wall_texture, t_ray ray_data,
		int wall_side)
{
	float	wall_x;
	int		texture_column;

	wall_x = calc_wall_pos(ray_data.impact, wall_side);
	flip_texture(wall_side, &wall_x, ray_data.dir);
	texture_column = (int)(wall_x * wall_texture->width);
	return (clamp_texture_coords(texture_column, wall_texture->width));
}

void	calc_y_bounds(t_wall wall, int *y_start, int *y_end)
{
	*y_start = (int)floor(wall.start);
	*y_end = (int)ceil(wall.end);
	if (*y_start < 0)
		*y_start = 0;
	if (*y_start >= HEIGHT)
		*y_start = HEIGHT - 1;
	if (*y_end > HEIGHT)
		*y_end = HEIGHT;
	if (*y_end < 0)
		*y_end = 0;
}
