/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarian <frmarian@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 13:10:58 by antonimo          #+#    #+#             */
/*   Updated: 2025/07/28 14:19:49 by frmarian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_image	*select_wall_texture(t_game *cub3d, int wall_side)
{
	if (wall_side == VERTICAL_HIT) // Hit x-side wall
	{
		if (cub3d->ray_data.dir.x > 0)
			return (&cub3d->wall_ea); // East wall
		else
			return (&cub3d->wall_we); // West wall
	}
	else // Hit y-side wall
	{
		if (cub3d->ray_data.dir.y > 0)
			return (&cub3d->wall_so); // South wall
		else
			return (&cub3d->wall_no); // North wall
	}
}

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

static int	clamp_texture_coords(int coordinate, int max_value)
{
	if (coordinate < 0)
		return (0);
	if (coordinate >= max_value)
		return (max_value - 1);
	return (coordinate);
}

static void	flip_texture(float wall_side, float *wall_x, t_coords ray_dir)
{
	if ((wall_side == VERTICAL_HIT && ray_dir.x < 0)
		|| (wall_side == HORIZONTAL_HIT && ray_dir.y > 0))
		*wall_x = 1.0f - *wall_x;
}

static int	process_tex_x(t_image *wall_texture, t_ray ray_data, int wall_side)
{
	float	wall_x;
	int		texture_x;

	wall_x = calc_wall_pos(ray_data.impact, wall_side);
	flip_texture(wall_side, &wall_x, ray_data.dir);
	texture_x = (int)(wall_x * wall_texture->width);
	return (clamp_texture_coords(texture_x, wall_texture->width));
}

typedef struct s_render_params
{
	char	*img_data;
	char	*tex_data;
	int		img_bpp_bytes;
	int		tex_bpp_bytes;
	int		img_line_size;
	int		tex_line_size;
	int		tex_height;
	int		tex_x_offset;
	int		img_x_offset;
}	t_render_params;

static void	initialize_render_params(t_render_params *params, t_game *cub3d, t_image *wall_texture, int texture_x, int angle_column)
{
	params->img_data = cub3d->image.data;
	params->tex_data = wall_texture->data;

	params->img_bpp_bytes = cub3d->image.bpp / 8;
	params->tex_bpp_bytes = wall_texture->bpp / 8;

	params->img_line_size = cub3d->image.size_line;
	params->tex_line_size = wall_texture->size_line;

	params->tex_height = wall_texture->height;

	params->tex_x_offset = texture_x * params->tex_bpp_bytes;
	params->img_x_offset = angle_column * params->img_bpp_bytes;
}

static void	copy_texture_pixel(t_render_params *params, int y, int texture_y)
{
	int	tex_offset;
	int	img_offset;

	texture_y = clamp_texture_coords(texture_y, params->tex_height);
	tex_offset = texture_y * params->tex_line_size + params->tex_x_offset;
	img_offset = y * params->img_line_size + params->img_x_offset;
	*(int*)(params->img_data + img_offset) = *(int*)(params->tex_data + tex_offset);
}

static void	calc_y_bounds(t_wall wall, int *y_start, int *y_end)
{
	// Use floor/ceil to ensure complete coverage and eliminate gaps
	*y_start = (int)floor(wall.start);
	*y_end = (int)ceil(wall.end);

	// Clamp to screen bounds
	if (*y_start < 0)
		*y_start = 0;
	if (*y_start >= HEIGHT)
		*y_start = HEIGHT - 1;
	if (*y_end > HEIGHT)
		*y_end = HEIGHT;
	if (*y_end < 0)
		*y_end = 0;
}

static void	render_column_pixels(t_render_params *params, float tex_step, float tex_pos, int y_start, int y_end)
{
    int		y;
    int		texture_y;
    float	current_tex_pos = tex_pos;

	y = y_start;
	while (y < y_end)
    {
        texture_y = clamp_texture_coords((int)current_tex_pos, params->tex_height);
        copy_texture_pixel(params, y, texture_y);
        current_tex_pos += tex_step;
		y++;
    }
}
void	render_wall_column(t_image *wall_texture, t_game *cub3d, t_wall wall, float angle_column)
{
    t_render_params	params;
    float			tex_step;
    float			tex_pos;
    int				tex_x;
    int				y_start;
    int				y_end;

	tex_pos = 0;
    tex_x = process_tex_x(wall_texture, cub3d->ray_data, wall.side);
    tex_step = (float)wall_texture->height / wall.height;
	if (wall.start < 0)
		tex_pos = (-wall.start) * tex_step;
    initialize_render_params(&params, cub3d, wall_texture, tex_x, angle_column);
    calc_y_bounds(wall, &y_start, &y_end);
    render_column_pixels(&params, tex_step, tex_pos, y_start, y_end);
}
