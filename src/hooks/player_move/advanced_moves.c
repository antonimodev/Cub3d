/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   advanced_moves.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonimo <antonimo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 11:59:58 by antonimo          #+#    #+#             */
/*   Updated: 2025/07/14 12:40:48 by antonimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	move_forward_right(t_game *cub3d)
{
	move_forward(cub3d);
	move_right(cub3d);
}

static void	move_forward_left(t_game *cub3d)
{
	move_forward(cub3d);
	move_left(cub3d);
}

static void	move_back_right(t_game *cub3d)
{
	move_back(cub3d);
	move_right(cub3d);
}

static void	move_back_left(t_game *cub3d)
{
	move_back(cub3d);
	move_left(cub3d);
}

void	advanced_move(t_game *cub3d)
{
	t_move		player_move;
	
	player_move = cub3d->player.move;
	if (player_move.forward && player_move.right)
		move_forward_right(cub3d);
	if (player_move.forward && player_move.left)
		move_forward_left(cub3d);
	if (player_move.back && player_move.right)
		move_back_right(cub3d);
	if (player_move.back && player_move.left)
		move_back_left(cub3d);
}
