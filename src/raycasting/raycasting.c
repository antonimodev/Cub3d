/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonimo <antonimo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 13:18:40 by antonimo          #+#    #+#             */
/*   Updated: 2025/07/14 14:22:56 by antonimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* static bool collision()
{
    
} */

void	raycast(t_game *cub3d)
{
    float   ray_x;
    float   ray_y;
    int i = 20000;

    float angle_start = cub3d->player.angle.current_angle - PI / 6; // -30°
    float angle_end = cub3d->player.angle.current_angle + PI / 6;   // +30°
    ray_x = cub3d->player.x;
    ray_y = cub3d->player.y;
    while(i--)
    {
        put_pixel(ray_x, ray_y, 0x5C8E31, cub3d);
        ray_x += cos(cub3d->player.angle.current_angle);
        ray_y += sin(cub3d->player.angle.current_angle);
    }
    i = 20000;
    ray_x = cub3d->player.x;
    ray_y = cub3d->player.y;
    while(i--)
    {
        put_pixel(ray_x, ray_y, 0x5C8E31, cub3d);
        ray_x += cos(angle_start);
        ray_y += sin(angle_start);
    }
    i = 20000;
    ray_x = cub3d->player.x;
    ray_y = cub3d->player.y;
    while(i--)
    {
        put_pixel(ray_x, ray_y, 0x5C8E31, cub3d);
        ray_x += cos(angle_end);
        ray_y += sin(angle_end);
    }
}
/* 
void foo(int ray_x, int ray_y, int i, t_game *cub3d)
{
    float dist;
    float height;
    int start_x;
    int start_y;
    int end;

    dist = distance(ray_x - cub3d->player.x, ray_y - cub3d->player.y);
    height = (64 / height) / 2;
    start_y = (HEIGHT - height) / 2;
    end = start_y + height;
    while (start_y < end)
    {
        put_pixel(i, start_y, 255, cub3d);
        start_y++;
    }
} */

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
    return sqrt(x * x + y *y);
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
static float   fixed_dist(float x1, float y1, float x2, float y2, t_game *cub3d)
{
    float   delta_x;
    float   delta_y;
    float   angle;
    float   fixed_distance;

    delta_x = x2 - x1;
    delta_y = y2 - y1;
    angle = atan2(delta_y, delta_x) - cub3d->player.angle.current_angle;
    fixed_distance = distance(delta_x, delta_y) * cos(angle);
    return (fixed_distance);
}
