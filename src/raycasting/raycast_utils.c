/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarian <frmarian@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 13:10:58 by antonimo          #+#    #+#             */
/*   Updated: 2025/07/23 14:17:34 by frmarian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_image	*select_wall_texture(t_game *cub3d, t_coords ray_dir, t_coords ray_pos, int *wall_side)
{
    float x_remainder = fmodf(ray_pos.x, BLOCK);
    float y_remainder = fmodf(ray_pos.y, BLOCK);
    
    // Calcular distancias una sola vez
    float x_dist = fminf(x_remainder, BLOCK - x_remainder);
    float y_dist = fminf(y_remainder, BLOCK - y_remainder);
    
    if (x_dist < y_dist)
    {
        *wall_side = 0; // Vertical wall
        if (ray_dir.x > 0)
            return (&cub3d->wall_ea); // East
        else
            return (&cub3d->wall_we); // West
    }
    else
    {
        *wall_side = 1; // Horizontal wall
        if (ray_dir.y > 0)
            return (&cub3d->wall_so); // South
        else
            return (&cub3d->wall_no); // North
    }
}

// Versión optimizada de calc_pixel_x
static int calc_pixel_x(t_image *wall_texture, t_coords ray_dir, t_coords ray_pos, int wall_side)
{
    float wall_x;
    
    if (wall_side == 0) // Vertical wall
    {
        wall_x = fmodf(ray_pos.y, BLOCK) / BLOCK;
        if (ray_dir.x < 0)
            wall_x = 1.0f - wall_x;
    }
    else // Horizontal wall
    {
        wall_x = fmodf(ray_pos.x, BLOCK) / BLOCK;
        if (ray_dir.y > 0)
            wall_x = 1.0f - wall_x;
    }

    int texture_x = (int)(wall_x * wall_texture->width);
    
    // Clamp más eficiente
    if (texture_x < 0) texture_x = 0;
    else if (texture_x >= wall_texture->width) texture_x = wall_texture->width - 1;

    return texture_x;
}

void	foo2(t_image *wall_texture, t_coords ray_dir, t_coords ray_pos,
              float wall_height, float start_y, float end, int angle_column, t_game *cub3d, int wall_side)
{
    t_coords texture_coords;
    float tex_step;
    float tex_pos;
    int y;
    int color;

    // Validate inputs
    if (!wall_texture || !wall_texture->data || angle_column < 0 || angle_column >= WIDTH)
        return;

    texture_coords.x = calc_pixel_x(wall_texture, ray_dir, ray_pos, wall_side);
    
    // Calculate texture step and starting position
    tex_step = (float)wall_texture->height / wall_height;
    tex_pos = (start_y - HEIGHT / 2 + wall_height / 2) * tex_step;

    y = (int)start_y;
    while (y < (int)end && y < HEIGHT)
    {
        if (y >= 0) // Only render visible pixels
        {
            texture_coords.y = (int)tex_pos;
            
            // Clamp texture coordinates
            if (texture_coords.y < 0)
                texture_coords.y = 0;
            if (texture_coords.y >= wall_texture->height) 
                texture_coords.y = wall_texture->height - 1;
            
            // Calculate pixel address with bounds checking
            int pixel_offset = (int)texture_coords.y * wall_texture->size_line + 
                              (int)texture_coords.x * (wall_texture->bpp / 8);
            
            if (pixel_offset >= 0 && pixel_offset < wall_texture->height * wall_texture->size_line)
            {
                color = *(int *)(wall_texture->data + pixel_offset);
                put_pixel(angle_column, y, color, &cub3d->image);
            }
        }
        
        tex_pos += tex_step;
        y++;
    }
}
