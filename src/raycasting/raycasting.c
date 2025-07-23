/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarian <frmarian@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 13:18:40 by antonimo          #+#    #+#             */
/*   Updated: 2025/07/23 14:16:22 by frmarian         ###   ########.fr       */
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

static void	draw_3d(t_game *cub3d, float angle_column, float angle_start)
{
    t_coords	ray;
    t_coords	ray_impact;
    t_coords	ray_relative;
    float		dist;
    float		wall_height;
    float		start_y;
    float		end;
    t_coords    ray_dir;
    t_image		*wall_texture;
	int			wall_side;
    float       step_size = 0.1f; // Paso más pequeño para mayor precisión

    ray = cub3d->player.coords;
    ray_dir.x = cos(angle_start);
    ray_dir.y = sin(angle_start);

    // Raycasting más preciso
    while(!collision(ray, cub3d->map.map))
    {
        ray.x += ray_dir.x * step_size;
        ray.y += ray_dir.y * step_size;
    }

    // Retroceder un paso para estar justo antes de la colisión
    ray.x -= ray_dir.x * step_size;
    ray.y -= ray_dir.y * step_size;
    
    // Avanzar con pasos muy pequeños para encontrar el punto exacto
    while(!collision(ray, cub3d->map.map))
    {
        ray.x += ray_dir.x * 0.01f;
        ray.y += ray_dir.y * 0.01f;
    }

    // Guardar las coordenadas absolutas del punto de impacto
    ray_impact = ray;
    
    // Calcular coordenadas relativas solo para la distancia
    ray_relative = process_ray(cub3d, ray);
    
    // Usar las coordenadas absolutas para seleccionar la textura
    wall_texture = select_wall_texture(cub3d, ray_dir, ray_impact, &wall_side);

    dist = fixed_dist(ray_relative, cub3d->player.angle.current_angle);
    wall_height = (BLOCK / dist) * WIDTH / 2;
    start_y = (HEIGHT - wall_height) / 2;
    end = start_y + wall_height;
    
    // Pasar las coordenadas absolutas del impacto para el texturizado
    foo2(wall_texture, ray_dir, ray_impact, wall_height, start_y, end, angle_column, cub3d, wall_side);
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
