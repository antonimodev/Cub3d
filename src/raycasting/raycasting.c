/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonimo <antonimo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 13:18:40 by antonimo          #+#    #+#             */
/*   Updated: 2025/07/11 12:37:13 by antonimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


void	display_frame(t_game *cub3d)
{
    mlx_put_image_to_window(cub3d->mlx, cub3d->window, cub3d->image, 0, 0);
}
