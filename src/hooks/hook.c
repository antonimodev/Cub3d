/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonimo <antonimo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 10:52:43 by antonimo          #+#    #+#             */
/*   Updated: 2025/07/08 19:02:23 by antonimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	handle_keypress(int key, void *param)
{
	t_game *cub3d = (t_game *)param;

	if (key == KEY_ESC)
	{
		cleanup_game(cub3d);
		exit(EXIT_SUCCESS);
	}
	if (key == KEY_W)
		// Move player forward
	else if (key == KEY_S)
		// Move player backward
	else if (key == KEY_A)
		// Move player left
	else if (key == KEY_D)
		// Move player right
	else if (key == KEY_LEFT)
		// Rotate player left
	else if (key == KEY_RIGHT)
		// Rotate player right
	return (0);
}

int	handle_close_window(void *param)
{
	t_game *cub3d = (t_game *)param;

	cleanup_game(cub3d);
	exit(EXIT_SUCCESS);
}
