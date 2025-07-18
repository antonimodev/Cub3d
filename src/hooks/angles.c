/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   angles.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonimo <antonimo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 12:00:23 by antonimo          #+#    #+#             */
/*   Updated: 2025/07/18 12:13:55 by antonimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_angles(t_player_pos *player)
{
	if (player->dir == NORTH)
        player->angle.current_angle = PI / 2;
    else if (player->dir == SOUTH)
        player->angle.current_angle = 3 * PI / 2;
    else if (player->dir == EAST)
        player->angle.current_angle = 0;
    else if (player->dir == WEST)
        player->angle.current_angle = PI;
}

void	normalize_angle(t_player_pos *player)
{
	if (player->angle.current_angle > 2 * PI)
		player->angle.current_angle = 0;
	else if (player->angle.current_angle < 0)
		player->angle.current_angle = 2 * PI;
}
