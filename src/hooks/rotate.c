/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonimo <antonimo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 12:14:56 by antonimo          #+#    #+#             */
/*   Updated: 2025/07/15 14:22:08 by antonimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rotate_player(t_player_pos *player)
{
	if (player->rotate.left)
		rotate_left(player);
	else if (player->rotate.right)
		rotate_right(player);
}

void	rotate_left(t_player_pos *player)
{
	player->angle.current_angle -= ANGLE_SPEED;
	normalize_angle(player);
}

void	rotate_right(t_player_pos *player)
{
	player->angle.current_angle += ANGLE_SPEED;
	normalize_angle(player);
}
