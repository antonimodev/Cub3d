/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarian <frmarian@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 10:53:23 by antonimo          #+#    #+#             */
/*   Updated: 2025/07/29 13:42:08 by frmarian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	init_mlx(t_game *cub3d)
{
	cub3d->mlx = mlx_init();
	if (!cub3d->mlx)
	{
		write_error("Failed to initialize MiniLibX.");
		return (false);
	}
	return (true);
}

static bool	init_window(t_game *cub3d)
{
	cub3d->window = mlx_new_window(cub3d->mlx, WIDTH, HEIGHT, "Cub3D");
	if (!cub3d->window)
	{
		write_error("Failed to create window.");
		return (false);
	}
	return (true);
}

static bool	init_image(t_game *cub3d)
{
	cub3d->image.ptr = mlx_new_image(cub3d->mlx, WIDTH, HEIGHT);
	if (!cub3d->image.ptr)
	{
		write_error("Failed to create image.");
		return (false);
	}
	return (true);
}

int	game_loop(void *param)
{
	t_game	*cub3d;

	cub3d = (t_game *)param;
	move_player(cub3d);
	rotate_player(&cub3d->player);
	render_frame(cub3d);
	return (0);
}

bool	init_game(t_game *cub3d)
{
	if (!init_mlx(cub3d))
	{
		cleanup_game(cub3d);
		return (false);
	}
	if (!init_window(cub3d))
	{
		cleanup_game(cub3d);
		return (false);
	}
	if (!init_image(cub3d))
	{
		cleanup_game(cub3d);
		return (false);
	}
	cub3d->image.data = mlx_get_data_addr(cub3d->image.ptr, &cub3d->image.bpp,
			&cub3d->image.size_line, &cub3d->image.endian);
	init_angles(&cub3d->player);
	init_textures(cub3d);
	get_map_size(cub3d);
	scale_coords(&cub3d->player.coords);
	hooks_setup(cub3d);
	mlx_put_image_to_window(cub3d->mlx, cub3d->window, cub3d->image.ptr, 0, 0);
	mlx_loop(cub3d->mlx);
	return (true);
}
