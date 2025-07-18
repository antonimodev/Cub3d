/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonimo <antonimo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 11:56:49 by antonimo          #+#    #+#             */
/*   Updated: 2025/07/18 12:57:12 by antonimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_player(t_player_pos *player)
{
	basic_move(player);
	advanced_move(player);
}

/* void	move_forward(t_game *cub3d)
{
	t_coords	new_pos;
	t_coords	old_pos;
	
	new_pos.x = cub3d->player.coords.x - 1;
	new_pos.y = cub3d->player.coords.y;
	new_pos.x = cub3d->player.x - 1;
	new_pos.y = cub3d->player.y;
	if (collision(cub3d, new_pos))
		return ;
	old_pos = cub3d->player.coords;
	old_pos = cub3d->player;
	move(cub3d, new_pos, old_pos);
}

void	move_left(t_game *cub3d)
{
	t_coords	new_pos;
	t_coords	old_pos;
	
	new_pos.x = cub3d->player.coords.x;
	new_pos.y = cub3d->player.coords.y - 1;
	new_pos.x = cub3d->player.x;
	new_pos.y = cub3d->player.y - 1;
	if (collision(cub3d, new_pos))
		return ;
	old_pos = cub3d->player.coords;
	old_pos = cub3d->player;
	move(cub3d, new_pos, old_pos);
}

void	move_back(t_game *cub3d)
{
	t_coords	new_pos;
	t_coords	old_pos;
	
	new_pos.x = cub3d->player.coords.x + 1;
	new_pos.y = cub3d->player.coords.y;
	new_pos.x = cub3d->player.coords.x + 1;
	new_pos.y = cub3d->player.coords.y;
	if (collision(cub3d, new_pos))
		return ;
	old_pos = cub3d->player.coords;
	old_pos = cub3d->player;
	move(cub3d, new_pos, old_pos);
}

void	move_right(t_game *cub3d)
{
	t_coords	new_pos;
	t_coords	old_pos;
	
	new_pos.x = cub3d->player.coords.x;
	new_pos.y = cub3d->player.coords.y + 1;
	new_pos.x = cub3d->player.coords.x;
	new_pos.y = cub3d->player.coords.y + 1;
	if (collision(cub3d, new_pos))
		return ;
	old_pos = cub3d->player.coords;
	old_pos = cub3d->player;
	move(cub3d, new_pos, old_pos);
}
 */