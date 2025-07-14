/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   angles.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonimo <antonimo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 12:00:23 by antonimo          #+#    #+#             */
/*   Updated: 2025/07/14 13:36:08 by antonimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_angles(t_game *cub3d)
{
	if (cub3d->player.dir == NORTH)
		cub3d->player.angle.current_angle = 3 * PI / 2;
	else if (cub3d->player.dir == SOUTH)
		cub3d->player.angle.current_angle = PI / 2;
	else if (cub3d->player.dir == EAST)
		cub3d->player.angle.current_angle = 0;
	else if (cub3d->player.dir == WEST)
		cub3d->player.angle.current_angle = PI;
}

void	normalize_angle(t_game *cub3d)
{
	if (cub3d->player.angle.current_angle > 2 * PI)
		cub3d->player.angle.current_angle = 0;
	else if (cub3d->player.angle.current_angle < 0)
		cub3d->player.angle.current_angle = 2 * PI;
}
