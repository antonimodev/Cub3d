/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarian <frmarian@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 13:18:40 by antonimo          #+#    #+#             */
/*   Updated: 2025/07/24 13:57:36 by frmarian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Calculate the fish-eye corrected distance between two points.
 * 
 * This function calculates the perpendicular distance from the player to a wall,
 * correcting for the fish-eye effect that occurs in raycasting. The fish-eye
 * effect makes objects appear curved at the edges of the screen. This correction
 * ensures that parallel walls appear parallel on screen.
 * 
 * @param x1 The x-coordinate of the first point (typically player position).
 * @param y1 The y-coordinate of the first point (typically player position).
 * @param x2 The x-coordinate of the second point (typically wall intersection).
 * @param y2 The y-coordinate of the second point (typically wall intersection).
 * @param cub3d Pointer to the game structure containing player angle information.
 * @return The corrected perpendicular distance as a float value.
 */
static float	fixed_dist(t_coords ray, float current_angle)
{
	float current_cos;
	float current_sin;

	current_cos = cos(current_angle);
	current_sin = sin(current_angle);
	return (ray.x * current_cos + ray.y * current_sin);
}

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
static bool collision(t_coords ray, t_map *map)
{
    int x;
    int y;

	x = (int)(ray.x / BLOCK);
	y = (int)(ray.y / BLOCK);
    // Bounds checking más eficiente
    if (x < 0 || y < 0 || y >= map->map_height)
	{
		printf("\nSE HA SALIDO DE LOS LIMITES\n");
		return true;
	}
	if (x >= (int)ft_strlen(map->map[y]))
        return true;
    return (map->map[y][x] == WALL);
}

/* static bool collision(t_coords ray, t_map *map)
{
    int x;
    int y;

    x = (int)(ray.x / BLOCK);
    y = (int)(ray.y / BLOCK);

    if (x < 0 || y < 0 || y >= map->map_height)
        return true;
    if (x >= (int)ft_strlen(map->map[y]))
        return true;

    return (map->map[y][x] == WALL);
} */


/* static void	draw_3d(t_game *cub3d, float angle_column, float angle_start)
{
    t_coords	ray;
    float		dist;
    float		wall_height;
    float		start_y;
    float		end;
    t_coords    ray_dir;
    t_image		*wall_texture;

    ray = cub3d->player.coords;
    ray_dir.x = cos(angle_start);
    ray_dir.y = sin(angle_start);

    while(!collision(ray, cub3d->map.map))
    {
        ray.x += ray_dir.x;
        ray.y += ray_dir.y;
    }
	t_coords	placeholder = ray;
    ray = process_ray(cub3d, ray);
    wall_texture = select_wall_texture(cub3d, ray_dir, placeholder);

    dist = fixed_dist(ray, cub3d->player.angle.current_angle);
    wall_height = (BLOCK / dist) * WIDTH / 2;
    start_y = (HEIGHT - wall_height) / 2;
    end = start_y + wall_height;
    // Usamos foo2 para pintar la columna texturizada
    foo2(wall_texture, ray_dir, placeholder, wall_height, start_y, end, angle_column, cub3d);
} */

static t_coords	cast_ray_coarse(t_coords ray, float ray_dir_x, float ray_dir_y, t_map map)
{
	float	step_size;

	step_size = 1.5f;
	while (!collision(ray, &map))
	{
		ray.x += ray_dir_x * step_size;
		ray.y += ray_dir_y * step_size;
	}
	ray.x -= ray_dir_x * step_size;
	ray.y -= ray_dir_y * step_size;
	return (ray);
}

static t_coords	cast_ray_fine(t_coords ray, float ray_dir_x, float ray_dir_y, t_map map)
{
	float	fine_step;

	fine_step = 0.1f;
	while (!collision(ray, &map))
	{
		ray.x += ray_dir_x * fine_step;
		ray.y += ray_dir_y * fine_step;
	}
	return (ray);
}

static void cast_ray(t_ray *ray_data, float cos_angle, float sin_angle, t_map map)
{
	ray_data->ray = cast_ray_coarse(ray_data->ray, cos_angle, sin_angle, map);
	ray_data->ray = cast_ray_fine(ray_data->ray, cos_angle, sin_angle, map);
}

static t_coords	calc_ray_dist(t_player_pos player, t_coords ray)
{
	ray.x = ray.x - player.coords.x;
	ray.y = ray.y - player.coords.y;
	return (ray);
}

static void	store_ray_data(t_ray *ray_data, t_player_pos player, float cos_angle, float sin_angle)
{
    ray_data->impact = ray_data->ray;
	ray_data->relative = calc_ray_dist(player, ray_data->ray);
	ray_data->dir.x = cos_angle;
	ray_data->dir.y = sin_angle;
}

static void	calc_column_bounds(float wall_height, float *start_y, float *end)
{
	*start_y = (HEIGHT - wall_height) / 2;
	*end = *start_y + wall_height;
}

static void	draw_3d_cached(t_game *cub3d, int angle_column, float cos_angle, float sin_angle)
{
	t_ray		ray_data;
	float		wall_height;
	float		start_y;
	float		end;
	int			wall_side;

	ray_data.ray = cub3d->player.coords;
    cast_ray(&ray_data, cos_angle, sin_angle, cub3d->map);
    store_ray_data(&ray_data, cub3d->player, cos_angle, sin_angle);
	wall_height = (BLOCK / fixed_dist
		(ray_data.relative, cub3d->player.angle.current_angle)) * WIDTH / 2;
	calc_column_bounds(wall_height, &start_y, &end);
	render_wall_column(select_wall_texture(cub3d, ray_data, &wall_side),
		ray_data, wall_height, start_y, end, angle_column, cub3d, wall_side);
}


static void	init_angle_cache(float *cos_cache, float *sin_cache, float angle_start, float angle_increment)
{
	float	current_angle;
	int		i;

	current_angle = angle_start;
	i = 0;
	while (i < WIDTH)
	{
		cos_cache[i] = cos(current_angle);
		sin_cache[i] = sin(current_angle);
		current_angle += angle_increment;
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
    float   angle_increment;
    float cos_cache[WIDTH];
    float sin_cache[WIDTH];
	
	angle_start = cub3d->player.angle.current_angle - PI / 6; // -30º
	angle_increment = (PI / 3) / WIDTH; // 60º / WIDTH = Xº per column
    init_angle_cache(cos_cache, sin_cache, angle_start, angle_increment);
    render_all_columns(cub3d, cos_cache, sin_cache);
}


/* void	raycast(t_game *cub3d) // DEBUG
{
    float   ray_x;
    float   ray_y;

    // start_x
    float angle_start = cub3d->player.angle.current_angle - PI / 6; // -30°
    //
    float angle_end = cub3d->player.angle.current_angle + PI / 6;   // +30°
    ray_x = cub3d->player.coords.x;
    ray_y = cub3d->player.coords.y;
    while(!collision(ray_x, ray_y, cub3d)) // straight ray
    {
        put_pixel(ray_x, ray_y, 0x424242, cub3d);
        ray_x += cos(cub3d->player.angle.current_angle);
        ray_y += sin(cub3d->player.angle.current_angle);
    }
    ray_x = cub3d->player.coords.x;
    ray_y = cub3d->player.coords.y;
    while(!collision(ray_x, ray_y, cub3d)) // diagonal left ray
    {
        put_pixel(ray_x, ray_y, 0x424242, cub3d);
        ray_x += cos(angle_start);
        ray_y += sin(angle_start);
    }
    ray_x = cub3d->player.coords.x;
    ray_y = cub3d->player.coords.y;
    while(!collision(ray_x, ray_y, cub3d)) // diagonal right ray
    {
        put_pixel(ray_x, ray_y, 0x424242, cub3d);
        ray_x += cos(angle_end);
        ray_y += sin(angle_end);
    }
} */
