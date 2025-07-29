/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarian <frmarian@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 11:56:49 by antonimo          #+#    #+#             */
/*   Updated: 2025/07/29 13:34:02 by frmarian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	scale_coords(t_coords *coords)
{
	int	temp_coord;

	temp_coord = coords->x;
	coords->x = coords->y * BLOCK + BLOCK / 2;
	coords->y = temp_coord * BLOCK + BLOCK / 2;
}

void	move_player(t_game *cub3d)
{
	basic_move(cub3d);
	advanced_move(cub3d);
}
