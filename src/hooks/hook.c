/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarian <frmarian@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 10:52:43 by antonimo          #+#    #+#             */
/*   Updated: 2025/07/29 13:34:27 by frmarian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	hooks_setup(t_game *cub3d)
{
	mlx_hook(cub3d->window, KEY_PRESSED, 1L << 0, handle_key_press, cub3d);
	mlx_hook(cub3d->window, KEY_RELEASED, 1L << 1, handle_key_release, cub3d);
	mlx_hook(cub3d->window, CLOSE_WINDOW, 0, handle_close_window, cub3d);
	mlx_loop_hook(cub3d->mlx, game_loop, cub3d);
}

int	handle_key_press(int key, void *param)
{
	t_game	*cub3d;

	cub3d = (t_game *)param;
	if (key == KEY_ESC)
		return (mlx_loop_end(cub3d->mlx));
	if (key == KEY_W)
		cub3d->player.move.forward = true;
	else if (key == KEY_S)
		cub3d->player.move.back = true;
	else if (key == KEY_A)
		cub3d->player.move.left = true;
	else if (key == KEY_D)
		cub3d->player.move.right = true;
	else if (key == KEY_LEFT)
		cub3d->player.rotate.left = true;
	else if (key == KEY_RIGHT)
		cub3d->player.rotate.right = true;
	return (0);
}

int	handle_key_release(int key, void *param)
{
	t_game	*cub3d;

	cub3d = (t_game *)param;
	if (key == KEY_W)
		cub3d->player.move.forward = false;
	else if (key == KEY_S)
		cub3d->player.move.back = false;
	else if (key == KEY_A)
		cub3d->player.move.left = false;
	else if (key == KEY_D)
		cub3d->player.move.right = false;
	else if (key == KEY_LEFT)
		cub3d->player.rotate.left = false;
	else if (key == KEY_RIGHT)
		cub3d->player.rotate.right = false;
	return (0);
}

int	handle_close_window(void *param)
{
	t_game	*cub3d;

	cub3d = (t_game *)param;
	return (mlx_loop_end(cub3d->mlx));
}
