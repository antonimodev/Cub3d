/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonimo <antonimo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 13:18:40 by antonimo          #+#    #+#             */
/*   Updated: 2025/07/08 13:19:16 by antonimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	render_frame(t_game *cub3d)
{
	// Clean image buffer

	// Render Floor and Ceiling
	
	// Raycasting loop
}

void	display_frame(t_game *cub3d)
{
    mlx_put_image_to_window(cub3d->mlx, cub3d->window, cub3d->image, 0, 0);
}
