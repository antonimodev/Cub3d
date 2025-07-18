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

static void	draw_3d(t_game *cub3d, float angle_column, float angle_start)
{
	t_coords	ray;
	float		dist;
	float		wall_height;
	float		start_y;
	float		end;

	ray = cub3d->player.coords;
	cub3d->player.angle.cos_angle = cos(angle_start);
	cub3d->player.angle.sin_angle = sin(angle_start);
    while(!collision(ray, cub3d->map.map)) // straight ray
    {
        //put_pixel(ray.x, ray.y, 0xFF0000, cub3d);
        ray.x += cub3d->player.angle.cos_angle;
        ray.y += cub3d->player.angle.sin_angle;
    }
	ray = process_ray(cub3d, ray);
	dist = fixed_dist(ray, cub3d->player.angle.current_angle);
    wall_height = (BLOCK / dist) * WIDTH / 2;
    start_y = (HEIGHT - wall_height) / 2;
    end = start_y + wall_height;
    while (start_y < end)
    {
        put_pixel(angle_column, start_y, 0xFFFFFF, cub3d);
        start_y++;
    }
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
