/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonimo <antonimo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 13:18:40 by antonimo          #+#    #+#             */
/*   Updated: 2025/07/25 14:18:31 by antonimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_map_size(t_game *cub3d)
{
	int	current_line;
	int	x;

	current_line = 0;
	x = 0;
	while (cub3d->map.map[x])
	{
		current_line = ft_strlen(cub3d->map.map[x]);
		if (current_line > cub3d->map.map_width)
			cub3d->map.map_width = current_line;
		x++;
	}
	cub3d->map.map_height = x;
}

static t_ray	cast_ray_dda(t_coords start, float cos_angle, float sin_angle, t_map map)
{
	t_ray	result;
	t_coords	map_pos;
	t_coords	step;
	t_coords	delta_dist;
	t_coords	side_dist;
	int		hit;
	int		side;
	float	perp_wall_dist;

	// Initialize ray data
	result.ray = start;
	result.dir.x = cos_angle;
	result.dir.y = sin_angle;

	// Convert to grid coordinates
	map_pos.x = (int)(start.x / BLOCK);
	map_pos.y = (int)(start.y / BLOCK);

	// Calculate delta distances (distance between x/y sides)
	if (cos_angle == 0)
		delta_dist.x = 1e30;
	else
		delta_dist.x = fabs(1.0 / cos_angle);

	if (sin_angle == 0)
		delta_dist.y = 1e30;
	else
		delta_dist.y = fabs(1.0 / sin_angle);
	

	// Calculate step direction and initial side distances
	if (cos_angle < 0)
	{
		step.x = -1;
		side_dist.x = ((start.x / BLOCK) - map_pos.x) * delta_dist.x;
	}
	else
	{
		step.x = 1;
		side_dist.x = (map_pos.x + 1.0 - (start.x / BLOCK)) * delta_dist.x;
	}
	
	if (sin_angle < 0)
	{
		step.y = -1;
		side_dist.y = ((start.y / BLOCK) - map_pos.y) * delta_dist.y;
	}
	else
	{
		step.y = 1;
		side_dist.y = (map_pos.y + 1.0 - (start.y / BLOCK)) * delta_dist.y;
	}
	
	// DDA main loop
	hit = 0;
	while (hit == 0)
	{
		// Jump to next map square, either in x-direction, or in y-direction
		if (side_dist.x < side_dist.y)
		{
			side_dist.x += delta_dist.x;
			map_pos.x += step.x;
			side = 0;
		}
		else
		{
			side_dist.y += delta_dist.y;
			map_pos.y += step.y;
			side = 1;
		}
		
		// Check bounds and wall collision
		if (map_pos.x < 0 || map_pos.y < 0 || map_pos.y >= map.map_height)
			break;
		if (map_pos.x >= (int)ft_strlen(map.map[(int)map_pos.y]))
			break;
		if (map.map[(int)map_pos.y][(int)map_pos.x] == WALL)
			hit = 1;
	}

	int temp = 0;
	
	// Calculate perpendicular wall distance (DDA style)
	if (side == 0)
	{
		if (step.x < 0)
			temp = 0;
		else
			temp = 1;
		perp_wall_dist = (map_pos.x - (start.x / BLOCK) + (1 - step.x) / 2) / cos_angle;
		result.impact.x = (map_pos.x + temp) * BLOCK;
		result.impact.y = start.y + perp_wall_dist * sin_angle * BLOCK;
	}
	else
	{
		if (step.x < 0)
			temp = 0;
		else
			temp = 1;
		perp_wall_dist = (map_pos.y - (start.y / BLOCK) + (1 - step.y) / 2) / sin_angle;
		result.impact.x = start.x + perp_wall_dist * cos_angle * BLOCK;
		result.impact.y = (map_pos.y + temp) * BLOCK;
	}

	// Store the actual distance in BLOCK units (not yet fish-eye corrected)
	result.relative.x = perp_wall_dist * BLOCK;
	result.relative.y = 0;
	
	// Store which side was hit (0 = x-side, 1 = y-side)
	result.ray.x = side; // Using ray.x temporarily to store side info
	
	return (result);
}

static void	calc_column_bounds(float wall_height, float *start_y, float *end)
{
	*start_y = (HEIGHT - wall_height) / 2;
	*end = *start_y + wall_height;
}

static float	get_wall_height(float cos_angle, float sin_angle, float current_angle, t_ray ray_data)
{
	float	angle_diff;
	float	fixed_dist;
	float	projection_distance;

	angle_diff = atan2(sin_angle, cos_angle) - current_angle;
	fixed_dist = ray_data.relative.x * cos(angle_diff);
	projection_distance = WIDTH / (2.0f * tan(PI / 6));
	return ((BLOCK * projection_distance) / fixed_dist);
}

static void	draw_3d_cached(t_game *cub3d, int angle_column, float cos_angle, float sin_angle)
{
	t_ray		ray_data;
	float		wall_height;
	float		start_y;
	float		end;
	int			wall_side;

	ray_data = cast_ray_dda(cub3d->player.coords, cos_angle, sin_angle, cub3d->map);
	wall_side = (int)ray_data.ray.x;
	ray_data.ray = ray_data.impact;  // Restore proper impact point
	wall_height = get_wall_height(cos_angle, sin_angle, cub3d->player.angle.current_angle, ray_data);
	calc_column_bounds(wall_height, &start_y, &end);
	render_wall_column(select_wall_texture_dda(cub3d, ray_data, wall_side),
		ray_data, wall_height, start_y, end, angle_column, cub3d, wall_side);
}

static void	init_angle_cache(float *cos_cache, float *sin_cache, float angle_start, float delta_angle)
{
	float	current_angle;
	int		i;

	current_angle = angle_start;
	i = 0;
	while (i < WIDTH)
	{
		cos_cache[i] = cos(current_angle);
		sin_cache[i] = sin(current_angle);
		current_angle += delta_angle;
		i++;
	}
}

static void	render_all_columns(t_game *cub3d, float *cos_cache, float *sin_cache)
{
	int	angle_column;

	angle_column = 0;
	while (angle_column < WIDTH) // Render all columns into WIDTH of the screen
	{
		draw_3d_cached(cub3d, angle_column, cos_cache[angle_column], sin_cache[angle_column]);
		angle_column++;
	}
}

void	raycast(t_game *cub3d)
{
    float	angle_start;
    float   delta_angle;
    float	cos_cache[WIDTH];
    float	sin_cache[WIDTH];

	angle_start = cub3d->player.angle.current_angle - PI / 6; // -30º
	delta_angle = (PI / 3) / WIDTH; // 60º / WIDTH = Xº per column
    init_angle_cache(cos_cache, sin_cache, angle_start, delta_angle);
    render_all_columns(cub3d, cos_cache, sin_cache);
}
