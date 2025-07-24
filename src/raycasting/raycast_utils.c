/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarian <frmarian@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 13:10:58 by antonimo          #+#    #+#             */
/*   Updated: 2025/07/24 14:10:12 by frmarian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_coords	calc_block_pos(t_coords ray_pos)
{
	t_coords	distance;
	float		x_in_block;
	float		y_in_block;

	x_in_block = ray_pos.x - (int)(ray_pos.x / BLOCK) * BLOCK;
	y_in_block = ray_pos.y - (int)(ray_pos.y / BLOCK) * BLOCK;
	if (x_in_block < BLOCK / 2)
		distance.x = x_in_block;
	else
		distance.x = BLOCK - x_in_block;
	if (y_in_block < BLOCK / 2)
		distance.y = y_in_block;
	else
		distance.y = BLOCK - y_in_block;
	return (distance);
}

t_image	*select_wall_texture(t_game *cub3d, t_ray ray_data, int *wall_side)
{
	t_coords	distances;

	distances = calc_block_pos(ray_data.ray);
	if (distances.x < distances.y)
	{
		*wall_side = 0;
		if (ray_data.dir.x > 0)
			return (&cub3d->wall_ea);
		else
			return (&cub3d->wall_we);
	}
	else
	{
		*wall_side = 1;
		if (ray_data.dir.y > 0)
			return (&cub3d->wall_so);
		else
			return (&cub3d->wall_no);
	}
}

static float	calc_wall_pos(t_coords ray_pos, int wall_side)
{
	float	wall_x;
	float	pos_in_block;

	if (wall_side == 0)
		pos_in_block = ray_pos.y - (int)(ray_pos.y / BLOCK) * BLOCK;
	else
		pos_in_block = ray_pos.x - (int)(ray_pos.x / BLOCK) * BLOCK;
	wall_x = pos_in_block / BLOCK;
	return (wall_x);
}

static float	adjust_wall_pos(float wall_x, t_coords ray_dir, int wall_side)
{
	if (wall_side == 0 && ray_dir.x < 0)
		return (1.0f - wall_x);
	if (wall_side == 1 && ray_dir.y > 0)
		return (1.0f - wall_x);
	return (wall_x);
}

static int	clamp_texture_coordinate(int coordinate, int max_value)
{
	if (coordinate < 0)
		return (0);
	if (coordinate >= max_value)
		return (max_value - 1);
	return (coordinate);
}

static int	calc_pixel_x(t_image *wall_texture, t_ray ray_data, int wall_side)
{
	float	wall_x;
	int		texture_x;

	wall_x = calc_wall_pos(ray_data.ray, wall_side);
	wall_x = adjust_wall_pos(wall_x, ray_data.dir, wall_side);
	texture_x = (int)(wall_x * wall_texture->width);
	return (clamp_texture_coordinate(texture_x, wall_texture->width));
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

	texture_y = clamp_texture_coordinate(texture_y, params->tex_height);
	tex_offset = texture_y * params->tex_line_size + params->tex_x_offset;
	img_offset = y * params->img_line_size + params->img_x_offset;
	*(int*)(params->img_data + img_offset) = *(int*)(params->tex_data + tex_offset);
}

static int	calc_y_bounds(float start_y, float end, int *y_start, int *y_end)
{
	*y_start = (int)start_y;
	*y_end = (int)end;
	if (*y_end > HEIGHT)
		*y_end = HEIGHT;
	return (1);
}

static void	render_column_pixels(t_render_params *params, float tex_step, float tex_pos, int y_start, int y_end)
{
	int		y;
	int		texture_y;
	float	current_tex_pos;

	current_tex_pos = tex_pos;
	y = y_start;
	while (y < y_end)
	{
		if (y >= 0)
		{
			texture_y = (int)current_tex_pos;
			copy_texture_pixel(params, y, texture_y);
		}
		current_tex_pos += tex_step;
		y++;
	}
}

void	render_wall_column(t_image *wall_texture, t_ray ray_data,
                        float wall_height, float start_y, float end, 
						int angle_column, t_game *cub3d, int wall_side)
{
	t_render_params	params;
	float			tex_step;
	float			tex_pos;
	int				texture_x;
	int				y_start;
	int				y_end;

	texture_x = calc_pixel_x(wall_texture, ray_data, wall_side);
	tex_step = (float)wall_texture->height / wall_height;
	tex_pos = (start_y - HEIGHT / 2 + wall_height / 2) * tex_step;
	initialize_render_params(&params, cub3d, wall_texture, texture_x, angle_column);
	calc_y_bounds(start_y, end, &y_start, &y_end);
	render_column_pixels(&params, tex_step, tex_pos, y_start, y_end);
}