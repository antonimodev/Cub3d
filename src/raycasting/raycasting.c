/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonimo <antonimo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 13:18:40 by antonimo          #+#    #+#             */
/*   Updated: 2025/07/18 13:56:06 by antonimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_coords	process_ray(t_game *cub3d, t_coords ray)
{
	ray.x = ray.x - cub3d->player.coords.x;
	ray.y = ray.y - cub3d->player.coords.y;
	return (ray);
}

/**
 * @brief Calculate the Euclidean distance between two points.
 * 
 * This function calculates the straight-line distance from the origin (0,0)
 * to the point (x,y) using the Pythagorean theorem: sqrt(x² + y²).
 * 
 * @param x The x-coordinate of the point.
 * @param y The y-coordinate of the point.
 * @return The Euclidean distance as a float value.
 */
static float   distance(float x, float y)
{
    return sqrt(x * x + y * y);
}

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
static float   fixed_dist(t_coords ray,
		float current_angle)
{
    float   angle;
    float   fixed_distance;

    angle = atan2(ray.y, ray.x) - current_angle;
    fixed_distance = distance(ray.x, ray.y) * cos(angle);
    return (fixed_distance);
}


static bool collision(t_coords ray, char **map)
{
    int x;
    int y;

    x = ray.x / BLOCK;
    y = ray.y / BLOCK;
    return (map[y][x] == WALL);
}

/* static void	draw_3d(t_game *cub3d, float angle_column, float angle_start)
	{
	t_coords	ray;
	float		dist;
	float		ray.wall_height;
	float		start_y;
	float		end;

	ray = cub3d->player.coords;
	cub3d->player.angle.cos_angle = cos(angle_start);
	cub3d->player.angle.sin_angle = sin(angle_start);
	while(!collision(ray, cub3d->map.map)) // straight ray
	{
		ray.x += cub3d->player.angle.cos_angle;
		ray.y += cub3d->player.angle.sin_angle;
	}
	set_ray_side(&cub3d->player.coords, ray); // TESTING
	ray = process_ray(cub3d, ray);
	dist = fixed_dist(ray, cub3d->player.angle.current_angle); // PERP WALL DIST
	wall_height = (BLOCK / dist) * WIDTH / 2; // LINE HEIGHT
	start_y = (HEIGHT - wall_height) / 2; // DRAW START
	end = start_y + wall_height; // DRAW END
	while (start_y < end)
	{
		put_pixel(angle_column, start_y, 0xFFFFFF, cub3d);
		start_y++;
	}
} */

static int	choose_texture(t_ray *ray)
{
    if (ray->side == VERTICAL_HIT)
    {
        if (ray->coords.x < 0)
            return NORTH;  /* rayo va hacia Oeste → muro Norte */
        else
            return SOUTH;  /* rayo va hacia Este  → muro Sur */
    }
    else
    {
        if (ray->coords.y < 0)
            return WEST;  /* rayo va hacia Norte → muro Oeste */
        else
            return EAST;  /* rayo va hacia Sur   → muro Este */
    }
}

static void	set_ray_side(t_coords *player, t_ray *ray)
{
	float delta_x;
	float delta_y;

	delta_y = fabs(ray->coords.y - player->y);
	delta_x = fabs(ray->coords.x - player->x);
	if (delta_x > delta_y)
		ray->side = VERTICAL_HIT; // Vertical crash wall
	else
		ray->side = HORIZONTAL_HIT; // Horizontal crash wall
}

static void draw_ray(t_game *cub3d, t_ray *ray, int column)
{
	int texture_id;
	double wall_impact_position;
	int texture_x;
	int pixel_y;
	int color;

	texture_id = choose_texture(ray);

	// Calcula la posición exacta del impacto en la pared (0–1 dentro del bloque)
	if (ray->side == VERTICAL_HIT)
		wall_impact_position = cub3d->player.coords.y + ray->fixed_dist * cub3d->player.angle.sin_angle;
	else
		wall_impact_position = cub3d->player.coords.x + ray->fixed_dist * cub3d->player.angle.cos_angle;
	wall_impact_position -= floor(wall_impact_position);

	// Convierte la posición de impacto a coordenada X en la textura
	texture_x = (int)(wall_impact_position * cub3d->wall_textures[texture_id]->width);

	// Espeja la textura si el impacto es desde el otro lado
	if ((ray->side == VERTICAL_HIT && ray->coords.x > 0) ||
		(ray->side == HORIZONTAL_HIT && ray->coords.y < 0))
		texture_x = cub3d->wall_textures[texture_id]->width - texture_x - 1;

	// Dibuja cada píxel vertical de la pared en la columna
	for (pixel_y = ray->drawStart; pixel_y < ray->drawEnd; pixel_y++)
	{
		int distance_from_center = pixel_y + (ray->wall_height / 2) - (HEIGHT / 2);
		int texture_y = (int)((distance_from_center * cub3d->wall_textures[texture_id]->height) / ray->wall_height);

		color = *(int *)(cub3d->wall_textures[texture_id]->data
			+ (texture_y * cub3d->wall_textures[texture_id]->size_line)
			+ (texture_x * (cub3d->wall_textures[texture_id]->bpp / 8)));

		put_pixel(column, pixel_y, color,
			cub3d->data,
			cub3d->size_line,
			cub3d->bpp);
	}
}

static void	draw_3d(t_game *cub3d, float angle_column, float angle_start)
{
	t_ray	ray;

	ray.coords = cub3d->player.coords;
	cub3d->player.angle.cos_angle = cos(angle_start);
	cub3d->player.angle.sin_angle = sin(angle_start);
	while(!collision(ray.coords, cub3d->map.map)) // straight ray
	{
		ray.coords.x += cub3d->player.angle.cos_angle;
		ray.coords.y += cub3d->player.angle.sin_angle;
	}
	set_ray_side(&cub3d->player.coords, &ray); // TESTING
	ray.coords = process_ray(cub3d, ray.coords);
	ray.fixed_dist = fixed_dist(ray.coords, cub3d->player.angle.current_angle); // PERP WALL DIST
	ray.wall_height = (BLOCK / ray.fixed_dist) * WIDTH / 2; // LINE HEIGHT
	ray.drawStart = (HEIGHT - ray.wall_height) / 2; // DRAW START
	ray.drawEnd = ray.drawStart + ray.wall_height; // DRAW END
	if (ray.drawStart < 0)
		ray.drawStart = 0;
	if (ray.drawEnd >= HEIGHT)
		ray.drawEnd = HEIGHT - 1;
	draw_ray(cub3d, &ray, angle_column);
}

void	raycast(t_game *cub3d) // DEBUG
{
    float	angle_start;
    float   angle_increment;
	int		angle_column;

    angle_start = cub3d->player.angle.current_angle - PI / 6; // 30º
    angle_increment = (PI / 3) / WIDTH; // num of radians to scale to WIDTH */
	angle_column = 0;
	while (angle_column < WIDTH)
	{
		draw_3d(cub3d, angle_column, angle_start);
		angle_start += angle_increment;
		angle_column++;
	}
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
