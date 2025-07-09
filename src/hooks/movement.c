/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonimo <antonimo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 10:52:53 by antonimo          #+#    #+#             */
/*   Updated: 2025/07/09 12:00:17 by antonimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_forward(t_game *cub3d)
{
	t_player_pos	new_pos;
	t_player_pos	old_pos;
	
	new_pos.x = cub3d->player_pos.x - 1;
	new_pos.y = cub3d->player_pos.y;
	if (collision(cub3d, new_pos))
		return ;
	old_pos = cub3d->player_pos;
	move(cub3d, new_pos, old_pos);
}

void	move_left(t_game *cub3d)
{
	t_player_pos	new_pos;
	t_player_pos	old_pos;
	
	new_pos.x = cub3d->player_pos.x;
	new_pos.y = cub3d->player_pos.y - 1;
	if (collision(cub3d, new_pos))
		return ;
	old_pos = cub3d->player_pos;
	move(cub3d, new_pos, old_pos);
}

void	move_back(t_game *cub3d)
{
	t_player_pos	new_pos;
	t_player_pos	old_pos;
	
	new_pos.x = cub3d->player_pos.x + 1;
	new_pos.y = cub3d->player_pos.y;
	if (collision(cub3d, new_pos))
		return ;
	old_pos = cub3d->player_pos;
	move(cub3d, new_pos, old_pos);
}

void	move_right(t_game *cub3d)
{
	t_player_pos	new_pos;
	t_player_pos	old_pos;
	
	new_pos.x = cub3d->player_pos.x;
	new_pos.y = cub3d->player_pos.y + 1;
	if (collision(cub3d, new_pos))
		return ;
	old_pos = cub3d->player_pos;
	move(cub3d, new_pos, old_pos);
}
