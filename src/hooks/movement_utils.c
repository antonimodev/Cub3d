/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonimo <antonimo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 12:00:23 by antonimo          #+#    #+#             */
/*   Updated: 2025/07/10 13:21:33 by antonimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move(t_game *cub3d, t_player_pos new_pos, t_player_pos old_pos)
{
	char player;

	player = cub3d->map.map[old_pos.x][old_pos.y];
	cub3d->map.map[new_pos.x][new_pos.y] = player;
	cub3d->map.map[old_pos.x][old_pos.y] = FLOOR;
	cub3d->player = new_pos;
}

bool	collision(t_game *cub3d, t_player_pos new_pos)
{
	return (cub3d->map.map[new_pos.x][new_pos.y] == WALL);
}
