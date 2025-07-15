/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   advanced_moves.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonimo <antonimo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 11:59:58 by antonimo          #+#    #+#             */
/*   Updated: 2025/07/15 14:17:12 by antonimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	move_forward_right(t_player_pos *player)
{
	move_forward(player);
	move_right(player);
}

static void	move_forward_left(t_player_pos *player)
{
	move_forward(player);
	move_left(player);
}

static void	move_back_right(t_player_pos *player)
{
	move_back(player);
	move_right(player);
}

static void	move_back_left(t_player_pos *player)
{
	move_back(player);
	move_left(player);
}

void	advanced_move(t_player_pos *player)
{
	if (player->move.forward && player->move.right)
		move_forward_right(player);
	if (player->move.forward && player->move.left)
		move_forward_left(player);
	if (player->move.back && player->move.right)
		move_back_right(player);
	if (player->move.back && player->move.left)
		move_back_left(player);
}
