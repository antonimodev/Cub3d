/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   advanced_moves.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonimo <antonimo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 11:59:58 by antonimo          #+#    #+#             */
/*   Updated: 2025/07/25 13:26:24 by antonimo         ###   ########.fr       */
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
	if (cub3d->player.move.forward && cub3d->player.move.right)
		move_forward_right(cub3d);
	if (cub3d->player.move.forward && cub3d->player.move.left)
		move_forward_left(cub3d);
	if (cub3d->player.move.back && cub3d->player.move.right)
		move_back_right(cub3d);
	if (cub3d->player.move.back && cub3d->player.move.left)
		move_back_left(cub3d);
}
