/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonimo <antonimo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 10:52:53 by antonimo          #+#    #+#             */
/*   Updated: 2025/07/11 14:25:05 by antonimo         ###   ########.fr       */
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

void	move_player(t_game *cub3d)
{
	basic_move(cub3d);
	advanced_move(cub3d);
}

void	move_forward(t_game *cub3d)
{
	cub3d->player.x += cub3d->player.angle.cos_angle * PLAYER_SPEED;
	cub3d->player.y += cub3d->player.angle.sin_angle * PLAYER_SPEED;
}

void	move_back(t_game *cub3d)
{
	cub3d->player.x -= cub3d->player.angle.cos_angle * PLAYER_SPEED;  // ← MENOS
	cub3d->player.y -= cub3d->player.angle.sin_angle * PLAYER_SPEED;  // ← MENOS
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
}

void	move_forward_right(t_game *cub3d)
{
	if (cub3d->player.move.forward && cub3d->player.move.right)
	{
		move_forward(cub3d);
		move_right(cub3d);
	}
}

void	move_forward_left(t_game *cub3d)
{
	if (cub3d->player.move.forward && cub3d->player.move.right)
	{
		move_forward(cub3d);
		move_left(cub3d);
	}
}

void	move_back_right(t_game *cub3d)
{
	if (cub3d->player.move.forward && cub3d->player.move.right)
	{
		move_back(cub3d);
		move_right(cub3d);
	}
}

void	move_back_left(t_game *cub3d)
{
	if (cub3d->player.move.forward && cub3d->player.move.right)
	{
		move_forward(cub3d);
		move_left(cub3d);
	}
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

void	advanced_move(t_game *cub3d)
{
	t_move		player_move;
	
	player_move = cub3d->player.move;
	if (player_move.forward && player_move.right)
	{
		move_forward(cub3d);
		move_right(cub3d);
	}
		if (player_move.forward && player_move.left)
	{
		move_forward(cub3d);
		move_left(cub3d);
	}
		if (player_move.back && player_move.right)
	{
		move_back(cub3d);
		move_right(cub3d);	
	}
		if (player_move.back && player_move.left)
	{
		move_back(cub3d);
		move_left(cub3d);
	}
}

void	rotate_player(t_game *cub3d)
{
	t_rotate	player_rotate;

	player_rotate = cub3d->player.rotate;
	if (cub3d->player.rotate.left)
		rotate_left(cub3d);
	else if (cub3d->player.rotate.right)
		rotate_right(cub3d);
}