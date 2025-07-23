/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarian <frmarian@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 10:53:23 by antonimo          #+#    #+#             */
/*   Updated: 2025/07/23 12:56:23 by frmarian         ###   ########.fr       */
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

// TO ORGANIZE:

void	put_pixel(int x, int y, int color, t_image *image)
{
	int index;

	if (x >= WIDTH || y >= HEIGHT || x < 0 || y < 0)
		return;
	index = y * image->size_line + x * image->bpp / 8;
	image->data[index] = color & 0xFF;
	image->data[index + 1] = (color >> 8) & 0xFF;
	image->data[index + 2] = (color >> 16) & 0xFF;
}

/* static void	clean_canvas(t_game *cub3d)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (x < 1920)
	{
		y = 0;
		while (y < 1080)
		{
			put_pixel(x, y, 0xFFC0CB, cub3d);
			y++;
		}
		x++;
	}
} */

void	draw_square(t_game *cub3d, int size, int x, int y) // TESTING, DON'T USE FOR :D
{
	for(int i = 0; i < size; i++) {
		put_pixel(x, y, 0x004200, &cub3d->image);
		x++;
	}
	for(int i = 0; i < size; i++) {
		put_pixel(x, y, 0x004200, &cub3d->image);
		y++;
	}
	for(int i = 0; i < size; i++) {
		put_pixel(x, y, 0x004200, &cub3d->image);
		x--;
	}
	for(int i = 0; i < size; i++) {
		put_pixel(x, y, 0x004200, &cub3d->image);
		y--;
	}
}

void	render_frame(t_game *cub3d)
{
    //clean_canvas(cub3d);
	draw_background(cub3d);
	printf("player x: %f, player y: %f \n", cub3d->player.coords.x, cub3d->player.coords.y);
	raycast(cub3d);
    //draw_square(cub3d, 10, cub3d->player.coords.x, cub3d->player.coords.y);
	//draw_walls(cub3d);
    mlx_put_image_to_window(cub3d->mlx, cub3d->window, cub3d->image.ptr, 0, 0);
}

static int	game_loop(void *param)
{
	t_game *cub3d;

	cub3d = (t_game *)param;
	move_player(&cub3d->player);
	rotate_player(&cub3d->player);
	render_frame(cub3d);
	return (0);
}

/* --------------------------------------------- */

static void scale_coords(t_coords *coords)
{
	int temp_coord;

	temp_coord = coords->x;
    coords->x = coords->y * BLOCK + BLOCK / 2;
	coords->y = temp_coord * BLOCK + BLOCK / 2;
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
	cub3d->image.data = mlx_get_data_addr(cub3d->image.ptr, &cub3d->image.bpp, &cub3d->image.size_line, &cub3d->image.endian);
	init_angles(&cub3d->player);
	init_textures(cub3d); // TESTING
	scale_coords(&cub3d->player.coords);
	mlx_hook(cub3d->window, KEY_PRESSED, 1L<<0, handle_key_press, cub3d);
	mlx_hook(cub3d->window, KEY_RELEASED, 1L<<1, handle_key_release, cub3d);
	mlx_hook(cub3d->window, CLOSE_WINDOW, 0, handle_close_window, cub3d);
	mlx_loop_hook(cub3d->mlx, game_loop, cub3d);
	mlx_put_image_to_window(cub3d->mlx, cub3d->window, cub3d->image.ptr, 0, 0);
	mlx_loop(cub3d->mlx);
	return (true);
}
