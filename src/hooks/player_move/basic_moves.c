/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_moves.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarian <frmarian@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 10:52:53 by antonimo          #+#    #+#             */
/*   Updated: 2025/07/29 13:41:59 by frmarian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_forward(t_game *cub3d)
{
	float	delta_x;
	float	delta_y;

	delta_x = cos(cub3d->player.angle.current_angle) * PLAYER_SPEED;
	delta_y = sin(cub3d->player.angle.current_angle) * PLAYER_SPEED;
	move_with_collision(cub3d, delta_x, delta_y);
}

void	move_back(t_game *cub3d)
{
	float	delta_x;
	float	delta_y;

	delta_x = -cos(cub3d->player.angle.current_angle) * PLAYER_SPEED;
	delta_y = -sin(cub3d->player.angle.current_angle) * PLAYER_SPEED;
	move_with_collision(cub3d, delta_x, delta_y);
}

void	move_left(t_game *cub3d)
{
	float	delta_x;
	float	delta_y;

	delta_x = sin(cub3d->player.angle.current_angle) * PLAYER_SPEED;
	delta_y = -cos(cub3d->player.angle.current_angle) * PLAYER_SPEED;
	move_with_collision(cub3d, delta_x, delta_y);
}

void	move_right(t_game *cub3d)
{
	float	delta_x;
	float	delta_y;

	delta_x = -sin(cub3d->player.angle.current_angle) * PLAYER_SPEED;
	delta_y = cos(cub3d->player.angle.current_angle) * PLAYER_SPEED;
	move_with_collision(cub3d, delta_x, delta_y);
}

void	basic_move(t_game *cub3d)
{
	if (cub3d->player.move.forward)
		move_forward(cub3d);
	else if (cub3d->player.move.back)
		move_back(cub3d);
	else if (cub3d->player.move.left)
		move_left(cub3d);
	else if (cub3d->player.move.right)
		move_right(cub3d);
}
