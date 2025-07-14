/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_moves.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonimo <antonimo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 10:52:53 by antonimo          #+#    #+#             */
/*   Updated: 2025/07/14 13:31:56 by antonimo         ###   ########.fr       */
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

/* void	move_forward(t_game *cub3d)
{
	cub3d->player.x += cub3d->player.angle.cos_angle * PLAYER_SPEED;
	cub3d->player.y += cub3d->player.angle.sin_angle * PLAYER_SPEED;
}

void	move_back(t_game *cub3d)
{
	cub3d->player.x -= cub3d->player.angle.cos_angle * PLAYER_SPEED;
	cub3d->player.y -= cub3d->player.angle.sin_angle * PLAYER_SPEED;
}

void	move_left(t_game *cub3d)
{
	cub3d->player.x += cub3d->player.angle.sin_angle * PLAYER_SPEED;  // ← sin
	cub3d->player.y -= cub3d->player.angle.cos_angle * PLAYER_SPEED;  // ← cos
}

void	move_right(t_game *cub3d)
{
	cub3d->player.x -= cub3d->player.angle.sin_angle * PLAYER_SPEED;  // ← -sin
	cub3d->player.y += cub3d->player.angle.cos_angle * PLAYER_SPEED;  // ← cos
} */

void	move_forward(t_game *cub3d)
{
	cub3d->player.x += cos(cub3d->player.angle.current_angle) * PLAYER_SPEED;
	cub3d->player.y += sin(cub3d->player.angle.current_angle) * PLAYER_SPEED;
}

void	move_back(t_game *cub3d)
{
	cub3d->player.x -= cos(cub3d->player.angle.current_angle) * PLAYER_SPEED;
	cub3d->player.y -= sin(cub3d->player.angle.current_angle) * PLAYER_SPEED;
}

void	move_left(t_game *cub3d)
{
	cub3d->player.x += sin(cub3d->player.angle.current_angle) * PLAYER_SPEED;  // ← sin
	cub3d->player.y -= cos(cub3d->player.angle.current_angle) * PLAYER_SPEED;  // ← cos
}

void	move_right(t_game *cub3d)
{
	cub3d->player.x -= sin(cub3d->player.angle.current_angle) * PLAYER_SPEED;  // ← -sin
	cub3d->player.y += cos(cub3d->player.angle.current_angle) * PLAYER_SPEED;  // ← cos
}

void	basic_move(t_game *cub3d)
{
	t_move		player_move;
	
	player_move = cub3d->player.move;
	if (player_move.forward)
		move_forward(cub3d);
	else if (player_move.back)
		move_back(cub3d);
	else if (player_move.left)
		move_left(cub3d);
	else if (player_move.right)
		move_right(cub3d);
}
