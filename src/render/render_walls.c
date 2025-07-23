/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_walls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarian <frmarian@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 12:55:55 by antonimo          #+#    #+#             */
/*   Updated: 2025/07/23 12:09:33 by frmarian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	foo(t_game *cub3d)
{
	init_textures(cub3d);
}

void	init_textures(t_game *cub3d)
{
	cub3d->wall_no.ptr = mlx_xpm_file_to_image(cub3d->mlx, cub3d->texture_paths.no, \
			&cub3d->wall_no.width, &cub3d->wall_no.height);
	cub3d->wall_so.ptr = mlx_xpm_file_to_image(cub3d->mlx, cub3d->texture_paths.so, \
			&cub3d->wall_so.width, &cub3d->wall_so.height);
	cub3d->wall_ea.ptr = mlx_xpm_file_to_image(cub3d->mlx, cub3d->texture_paths.ea, \
			&cub3d->wall_ea.width, &cub3d->wall_ea.height);
	cub3d->wall_we.ptr = mlx_xpm_file_to_image(cub3d->mlx, cub3d->texture_paths.we, \
			&cub3d->wall_we.width, &cub3d->wall_we.height);

	cub3d->wall_no.data = mlx_get_data_addr(cub3d->wall_no.ptr, &cub3d->wall_no.bpp, \
			&cub3d->wall_no.size_line, &cub3d->wall_no.endian);
	cub3d->wall_so.data = mlx_get_data_addr(cub3d->wall_so.ptr, &cub3d->wall_so.bpp, \
			&cub3d->wall_so.size_line, &cub3d->wall_so.endian);
	cub3d->wall_ea.data = mlx_get_data_addr(cub3d->wall_ea.ptr, &cub3d->wall_ea.bpp, \
			&cub3d->wall_ea.size_line, &cub3d->wall_ea.endian);
	cub3d->wall_we.data = mlx_get_data_addr(cub3d->wall_we.ptr, &cub3d->wall_we.bpp, \
			&cub3d->wall_we.size_line, &cub3d->wall_we.endian);
}

void	draw_walls(t_game *cub3d)
{
	int	x;
	int	y;

	x = 0;
	while (cub3d->map.map[x])
	{
		y = 0;
		while (cub3d->map.map[x][y])
		{
			if (cub3d->map.map[x][y] == WALL)
				draw_square(cub3d, BLOCK, x * BLOCK, y * BLOCK);
			y++;
		}
		x++;
	}
}