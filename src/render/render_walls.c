/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_walls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonimo <antonimo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 12:55:55 by antonimo          #+#    #+#             */
/*   Updated: 2025/07/18 14:25:25 by antonimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_texture(t_game *cub3d, int tex_id, char *path)
{
	cub3d->wall_textures[tex_id]->ptr = mlx_xpm_file_to_image(
		cub3d->mlx, path,
		&cub3d->wall_textures[tex_id]->width,
		&cub3d->wall_textures[tex_id]->height);
	cub3d->wall_textures[tex_id]->data = mlx_get_data_addr(
		cub3d->wall_textures[tex_id]->ptr,
		&cub3d->wall_textures[tex_id]->bpp,
		&cub3d->wall_textures[tex_id]->size_line,
		&cub3d->wall_textures[tex_id]->endian);
}

void	load_textures(t_game *cub3d)
{
	init_texture(cub3d, TEXTURE_NORTH, cub3d->texture_paths.no);
	init_texture(cub3d, TEXTURE_SOUTH, cub3d->texture_paths.so);
	init_texture(cub3d, TEXTURE_EAST, cub3d->texture_paths.ea);
	init_texture(cub3d, TEXTURE_WEST, cub3d->texture_paths.we);
}
