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

void	foo(t_game *cub3d)
{
	init_textures(cub3d);
}

void	init_textures(t_game *cub3d)
{
	cub3d->wall_ea.ptr = mlx_xpm_file_to_image(cub3d->mlx, cub3d->texture_paths.no, \
			&cub3d->wall_no.width, &cub3d->wall_no.height);
	cub3d->wall_ea.ptr = mlx_xpm_file_to_image(cub3d->mlx, cub3d->texture_paths.so, \
			&cub3d->wall_so.width, &cub3d->wall_so.height);
	cub3d->wall_ea.ptr = mlx_xpm_file_to_image(cub3d->mlx, cub3d->texture_paths.ea, \
			&cub3d->wall_ea.width, &cub3d->wall_ea.height);
	cub3d->wall_we.ptr = mlx_xpm_file_to_image(cub3d->mlx, cub3d->texture_paths.we, \
			cub3d->wall_we.width, &cub3d->wall_we.height);
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