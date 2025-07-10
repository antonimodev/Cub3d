/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonimo <antonimo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 10:53:23 by antonimo          #+#    #+#             */
/*   Updated: 2025/07/10 12:14:27 by antonimo         ###   ########.fr       */
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
	cub3d->image = mlx_new_image(cub3d->mlx, WIDTH, HEIGHT);
	if (!cub3d->image)
	{
		write_error("Failed to create image.");
		return (false);
	}
	return (true);
}

/* TESTING 
static void put_pixel(int x, int y, int color, t_game *cub3d)
{
	int index;

	if(x >= WIDTH || y >= HEIGHT || x < 0 || y < 0)
		return;
	index = y * cub3d->size_line + x * cub3d->bpp / 8;
	cub3d->data[index] = color & 0xFF;
	cub3d->data[index + 1] = (color >> 8) & 0xFF;
	cub3d->data[index + 2] = (color >> 16) & 0xFF;
} */

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

	// TESTING
	//cub3d->data = mlx_get_data_addr(cub3d->image, &cub3d->bpp, &cub3d->size_line, &cub3d->endian);
	mlx_key_hook(cub3d->window, handle_keypress, cub3d);
	mlx_hook(cub3d->window, CLOSE_WINDOW, 0, handle_close_window, cub3d);
	// TESTING
	//put_pixel(5, 5, 0xFFFF00, cub3d);
	return (true);
}
