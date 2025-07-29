/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarian <frmarian@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 13:39:11 by antonimo          #+#    #+#             */
/*   Updated: 2025/07/29 13:39:21 by frmarian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_pixel(int x, int y, int color, t_image *image)
{
	int	index;

	if (x >= WIDTH || y >= HEIGHT || x < 0 || y < 0)
		return ;
	index = y * image->size_line + x * image->bpp / 8;
	image->data[index] = color & 0xFF;
	image->data[index + 1] = (color >> 8) & 0xFF;
	image->data[index + 2] = (color >> 16) & 0xFF;
}

void	render_frame(t_game *cub3d)
{
	draw_background(cub3d);
	raycast(cub3d);
	mlx_put_image_to_window(cub3d->mlx, cub3d->window, cub3d->image.ptr, 0, 0);
}
