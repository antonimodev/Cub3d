/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarian <frmarian@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 12:55:55 by antonimo          #+#    #+#             */
/*   Updated: 2025/07/29 13:46:42 by frmarian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	load_texture(t_game *cub3d, t_image *tex, char *path)
{
	tex->ptr = mlx_xpm_file_to_image(cub3d->mlx, path, &tex->width,
			&tex->height);
	tex->data = mlx_get_data_addr(tex->ptr, &tex->bpp, &tex->size_line,
			&tex->endian);
}

void	init_textures(t_game *cub3d)
{
	load_texture(cub3d, &cub3d->wall_no, cub3d->texture_paths.no);
	load_texture(cub3d, &cub3d->wall_so, cub3d->texture_paths.so);
	load_texture(cub3d, &cub3d->wall_ea, cub3d->texture_paths.ea);
	load_texture(cub3d, &cub3d->wall_we, cub3d->texture_paths.we);
}

t_image	*select_wall_texture(t_game *cub3d, int wall_side)
{
	if (wall_side == VERTICAL_HIT)
	{
		if (cub3d->ray_data.dir.x > 0)
			return (&cub3d->wall_ea);
		else
			return (&cub3d->wall_we);
	}
	else
	{
		if (cub3d->ray_data.dir.y > 0)
			return (&cub3d->wall_so);
		else
			return (&cub3d->wall_no);
	}
}
