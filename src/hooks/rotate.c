/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonimo <antonimo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 12:14:56 by antonimo          #+#    #+#             */
/*   Updated: 2025/07/10 13:21:38 by antonimo         ###   ########.fr       */
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

	cub3d->player.angle.cos_angle = cos(cub3d->player.angle.current_angle);
	cub3d->player.angle.sin_angle = sin(cub3d->player.angle.current_angle);
	cub3d->player.angle.angle_speed = ANGLE_SPEED; // may be deleted because angle speed is const defined
}

void	normalize_angle(t_game *cub3d)
{
	if (cub3d->player.angle.current_angle > 2 * PI)
		cub3d->player.angle.current_angle = 0;
	else if (cub3d->player.angle.current_angle < 0)
		cub3d->player.angle.current_angle = 2 * PI;
}

void	rotate_left(t_game *cub3d)
{
	cub3d->player.angle.current_angle -= ANGLE_SPEED;
	normalize_angle(cub3d);
}

void	rotate_right(t_game *cub3d)
{
	cub3d->player.angle.current_angle += ANGLE_SPEED;
	normalize_angle(cub3d);
}