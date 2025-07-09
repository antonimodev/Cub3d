/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonimo <antonimo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 10:52:43 by antonimo          #+#    #+#             */
/*   Updated: 2025/07/09 13:51:37 by antonimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	handle_keypress(int key, void *param)
{
	t_game *cub3d;
	
	cub3d = (t_game *)param;
	if (key == KEY_ESC)
		return (mlx_loop_end(cub3d->mlx));
	if (key == KEY_W)
		move_forward(cub3d);
	else if (key == KEY_S)
		move_back(cub3d);
	else if (key == KEY_A)
		move_left(cub3d);
	else if (key == KEY_D)
		move_right(cub3d);
/* 	else if (key == KEY_LEFT)
		// Rotate camera to left
	else if (key == KEY_RIGHT)
		// Rotate camera to right */
	printf("\n\n");
	print_matrix(cub3d->map.map);
	printf("\n\n");
	return (0);
}

int	handle_close_window(void *param)
{
	t_game *cub3d;
	
	cub3d = (t_game *)param;
	return (mlx_loop_end(cub3d->mlx));
}
