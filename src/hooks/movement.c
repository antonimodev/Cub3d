/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonimo <antonimo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 10:52:53 by antonimo          #+#    #+#             */
/*   Updated: 2025/07/10 14:05:24 by antonimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* void	move_forward(t_game *cub3d)
{
	t_player_pos	new_pos;
	t_player_pos	old_pos;
	
	new_pos.x = cub3d->player.x - 1;
	new_pos.y = cub3d->player.y;
	if (collision(cub3d, new_pos))
		return ;
	old_pos = cub3d->player;
	move(cub3d, new_pos, old_pos);
}

void	move_left(t_game *cub3d)
{
	t_player_pos	new_pos;
	t_player_pos	old_pos;
	
	new_pos.x = cub3d->player.x;
	new_pos.y = cub3d->player.y - 1;
	if (collision(cub3d, new_pos))
		return ;
	old_pos = cub3d->player;
	move(cub3d, new_pos, old_pos);
}

void	move_back(t_game *cub3d)
{
	t_player_pos	new_pos;
	t_player_pos	old_pos;
	
	new_pos.x = cub3d->player.x + 1;
	new_pos.y = cub3d->player.y;
	if (collision(cub3d, new_pos))
		return ;
	old_pos = cub3d->player;
	move(cub3d, new_pos, old_pos);
}

void	move_right(t_game *cub3d)
{
	t_player_pos	new_pos;
	t_player_pos	old_pos;
	
	new_pos.x = cub3d->player.x;
	new_pos.y = cub3d->player.y + 1;
	if (collision(cub3d, new_pos))
		return ;
	old_pos = cub3d->player;
	move(cub3d, new_pos, old_pos);
}
 */

void move_forward(t_game *cub3d)
{
    cub3d->player.x += cub3d->player.angle.cos_angle * PLAYER_SPEED;
    cub3d->player.y += cub3d->player.angle.sin_angle * PLAYER_SPEED;
}

void move_back(t_game *cub3d)
{
    cub3d->player.x -= cub3d->player.angle.cos_angle * PLAYER_SPEED;  // ← MENOS
    cub3d->player.y -= cub3d->player.angle.sin_angle * PLAYER_SPEED;  // ← MENOS
}

void move_left(t_game *cub3d)  // Movimiento lateral (perpendicular)
{
    cub3d->player.x += cub3d->player.angle.sin_angle * PLAYER_SPEED;  // ← sin
    cub3d->player.y -= cub3d->player.angle.cos_angle * PLAYER_SPEED;  // ← cos
}

void move_right(t_game *cub3d)  // Movimiento lateral (perpendicular)
{
    cub3d->player.x -= cub3d->player.angle.sin_angle * PLAYER_SPEED;  // ← -sin
    cub3d->player.y += cub3d->player.angle.cos_angle * PLAYER_SPEED;  // ← cos
}