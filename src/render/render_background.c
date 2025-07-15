/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_background.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonimo <antonimo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 12:21:41 by antonimo          #+#    #+#             */
/*   Updated: 2025/07/15 13:50:10 by antonimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	color_to_hex(t_colors color)
{
    return ((color.red << 16) | (color.green << 8) | color.blue);
}

void	draw_background(t_game *cub3d)
{
	int	x;
	int	y;

	y = 0;
	while (y < HEIGHT / 2)
	{
		x = 0;
		while (x < WIDTH)
		{
			put_pixel(x, y, color_to_hex(cub3d->colors.ceiling), cub3d);
			x++;
		}
		y++;
	}
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			put_pixel(x, y, color_to_hex(cub3d->colors.floor), cub3d);
			x++;
		}
		y++;
	}
}
