/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   columns.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarian <frmarian@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 13:28:00 by antonimo          #+#    #+#             */
/*   Updated: 2025/07/29 14:12:34 by frmarian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_render_params	initialize_render_params(t_game *cub3d,
		t_image *wall_texture, int column_index, int angle_column)
{
	t_render_params	params;

	params.img_data = cub3d->image.data;
	params.tex_data = wall_texture->data;
	params.img_bpp_bytes = cub3d->image.bpp / 8;
	params.tex_bpp_bytes = wall_texture->bpp / 8;
	params.img_line_size = cub3d->image.size_line;
	params.tex_line_size = wall_texture->size_line;
	params.tex_height = wall_texture->height;
	params.tex_x_offset = column_index * params.tex_bpp_bytes;
	params.img_x_offset = angle_column * params.img_bpp_bytes;
	return (params);
}

static void	copy_texture_pixel(t_render_params *params, int y, int texture_y)
{
	int	tex_offset;
	int	img_offset;

	texture_y = clamp_texture_coords(texture_y, params->tex_height);
	tex_offset = texture_y * params->tex_line_size + params->tex_x_offset;
	img_offset = y * params->img_line_size + params->img_x_offset;
	*(int *)(params->img_data + img_offset) = *(int *)(params->tex_data
			+ tex_offset);
}

static void	render_column_pixels(t_render_params *params, int y_start,
		int y_end)
{
	int		y;
	int		texture_y;
	float	current_tex_pos;

	current_tex_pos = params->tex_pos;
	y = y_start;
	while (y < y_end)
	{
		texture_y = clamp_texture_coords((int)current_tex_pos,
				params->tex_height);
		copy_texture_pixel(params, y, texture_y);
		current_tex_pos += params->tex_step;
		y++;
	}
}

void	render_all_columns(t_game *cub3d, float *cos_cache, float *sin_cache)
{
	int	angle_column;

	angle_column = 0;
	while (angle_column < WIDTH)
	{
		draw_3d_cached(cub3d, angle_column, cos_cache[angle_column],
			sin_cache[angle_column]);
		angle_column++;
	}
}

void	render_wall_column(t_image *wall_texture, t_game *cub3d, t_wall wall,
		float angle_column)
{
	t_render_params	params;
	t_render_params	temp;
	int				column_index;
	int				y_start;
	int				y_end;

	temp.tex_pos = 0;
	column_index = get_texture_column(wall_texture, cub3d->ray_data, wall.side);
	temp.tex_step = (float)wall_texture->height / wall.height;
	if (wall.start < 0)
		temp.tex_pos = (-wall.start) * temp.tex_step;
	params = initialize_render_params(cub3d, wall_texture, column_index,
			angle_column);
	params.tex_pos = temp.tex_pos;
	params.tex_step = temp.tex_step;
	calc_y_bounds(wall, &y_start, &y_end);
	render_column_pixels(&params, y_start, y_end);
}
