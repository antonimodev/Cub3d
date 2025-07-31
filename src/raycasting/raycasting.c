/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonimo <antonimo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 13:18:40 by antonimo          #+#    #+#             */
/*   Updated: 2025/07/31 12:31:27 by antonimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	set_column_bounds(t_wall *wall)
{
	wall->start = (HEIGHT - wall->height) / 2;
	wall->end = wall->start + wall->height;
}

static float	get_wall_height(float cos_angle, float sin_angle,
		float current_angle, t_ray ray_data)
{
	float	angle_diff;
	float	fixed_dist;
	float	projection_distance;

	angle_diff = atan2(sin_angle, cos_angle) - current_angle;
	fixed_dist = ray_data.relative.x * cos(angle_diff);
	projection_distance = WIDTH / (2.0f * tan(PI / 6));
	return ((BLOCK * projection_distance) / fixed_dist);
}

void	draw_3d_cached(t_game *cub3d, int angle_column, float cos_angle,
		float sin_angle)
{
	t_wall	wall;
	t_image	*wall_texture;

	cub3d->ray_data = cast_ray_dda(cub3d->player.coords, cos_angle, sin_angle,
			cub3d->map);
	wall.side = (int)cub3d->ray_data.ray.x;
	wall_texture = select_wall_texture(cub3d, wall.side);
	cub3d->ray_data.ray = cub3d->ray_data.impact;
	wall.height = get_wall_height(cos_angle, sin_angle,
			cub3d->player.angle.current_angle, cub3d->ray_data);
	set_column_bounds(&wall);
	render_wall_column(wall_texture, cub3d, wall, angle_column);
}

static void	init_angle_cache(float *cos_cache, float *sin_cache,
		float angle_start, float delta_angle)
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

void	raycast(t_game *cub3d)
{
	float	angle_start;
	float	delta_angle;
	float	cos_cache[WIDTH];
	float	sin_cache[WIDTH];

	angle_start = cub3d->player.angle.current_angle - PI / 6;
	delta_angle = (PI / 3) / WIDTH;
	init_angle_cache(cos_cache, sin_cache, angle_start, delta_angle);
	render_all_columns(cub3d, cos_cache, sin_cache);
}
