/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_moves.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonimo <antonimo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 10:52:53 by antonimo          #+#    #+#             */
/*   Updated: 2025/07/16 12:37:48 by antonimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* void	move_forward(t_game *cub3d)
{
	t_player_pos	new_pos;
	t_player_pos	old_pos;
	
	new_pos.x = cub3d->player.coords.x - 1;
	new_pos.y = cub3d->player.coords.y;
	if (collision(cub3d, new_pos))
		return ;
	old_pos = cub3d->player;
	move(cub3d, new_pos, old_pos);
}

void	move_left(t_game *cub3d)
{
	t_player_pos	new_pos;
	t_player_pos	old_pos;
	
	new_pos.x = cub3d->player.coords.x;
	new_pos.y = cub3d->player.coords.y - 1;
	if (collision(cub3d, new_pos))
		return ;
	old_pos = cub3d->player;
	move(cub3d, new_pos, old_pos);
}

void	move_back(t_game *cub3d)
{
	t_player_pos	new_pos;
	t_player_pos	old_pos;
	
	new_pos.x = cub3d->player.coords.x + 1;
	new_pos.y = cub3d->player.coords.y;
	if (collision(cub3d, new_pos))
		return ;
	old_pos = cub3d->player;
	move(cub3d, new_pos, old_pos);
}

void	move_right(t_game *cub3d)
{
	t_player_pos	new_pos;
	t_player_pos	old_pos;
	
	new_pos.x = cub3d->player.coords.x;
	new_pos.y = cub3d->player.coords.y + 1;
	if (collision(cub3d, new_pos))
		return ;
	old_pos = cub3d->player;
	move(cub3d, new_pos, old_pos);
}
 */

/* void	move_forward(t_game *cub3d)
{
	cub3d->player.coords.x += cub3d->player.angle.cos_angle * PLAYER_SPEED;
	cub3d->player.coords.y += cub3d->player.angle.sin_angle * PLAYER_SPEED;
}

void	move_back(t_game *cub3d)
{
	cub3d->player.coords.x -= cub3d->player.angle.cos_angle * PLAYER_SPEED;
	cub3d->player.coords.y -= cub3d->player.angle.sin_angle * PLAYER_SPEED;
}

void	move_left(t_game *cub3d)
{
	cub3d->player.coords.x += cub3d->player.angle.sin_angle * PLAYER_SPEED;  // ← sin
	cub3d->player.coords.y -= cub3d->player.angle.cos_angle * PLAYER_SPEED;  // ← cos
}

void	move_right(t_game *cub3d)
{
	cub3d->player.coords.x -= cub3d->player.angle.sin_angle * PLAYER_SPEED;  // ← -sin
	cub3d->player.coords.y += cub3d->player.angle.cos_angle * PLAYER_SPEED;  // ← cos
} */

void	move_forward(t_player_pos *player)
{
	player->coords.x += cos(player->angle.current_angle) * PLAYER_SPEED;
	player->coords.y += sin(player->angle.current_angle) * PLAYER_SPEED;
}

void	move_back(t_player_pos *player)
{
	player->coords.x -= cos(player->angle.current_angle) * PLAYER_SPEED;
	player->coords.y -= sin(player->angle.current_angle) * PLAYER_SPEED;
}

void	move_left(t_player_pos *player)
{
	player->coords.x += sin(player->angle.current_angle) * PLAYER_SPEED;  // ← sin
	player->coords.y -= cos(player->angle.current_angle) * PLAYER_SPEED;  // ← cos
}

void	move_right(t_player_pos *player)
{
	player->coords.x -= sin(player->angle.current_angle) * PLAYER_SPEED;  // ← -sin
	player->coords.y += cos(player->angle.current_angle) * PLAYER_SPEED;  // ← cos
}

void	basic_move(t_player_pos *player)
{
	if (player->move.forward)
		move_forward(player);
	else if (player->move.back)
		move_back(player);
	else if (player->move.left)
		move_left(player);
	else if (player->move.right)
		move_right(player);
}
