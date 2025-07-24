/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarian <frmarian@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 11:00:50 by antonimo          #+#    #+#             */
/*   Updated: 2025/07/24 11:46:18 by frmarian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	cleanup_game_textures(t_game *cub3d)
{
	if (cub3d->texture_paths.no)
	{
		free(cub3d->texture_paths.no);
		mlx_destroy_image(cub3d->mlx, cub3d->wall_no.ptr);
	}
	if (cub3d->texture_paths.so)
	{
		free(cub3d->texture_paths.so);
		mlx_destroy_image(cub3d->mlx, cub3d->wall_so.ptr);
	}
	if (cub3d->texture_paths.ea)
	{
		free(cub3d->texture_paths.ea);
		mlx_destroy_image(cub3d->mlx, cub3d->wall_ea.ptr);
	}
	if (cub3d->texture_paths.we)
	{
		free(cub3d->texture_paths.we);
		mlx_destroy_image(cub3d->mlx, cub3d->wall_we.ptr);
	}
}

static void	cleanup_game_mlx(t_game *cub3d)
{
	if (cub3d->image.ptr)
		mlx_destroy_image(cub3d->mlx, cub3d->image.ptr);
	if (cub3d->window)
		mlx_destroy_window(cub3d->mlx, cub3d->window);
	if (cub3d->mlx)
		mlx_destroy_display(cub3d->mlx);
}

static void	cleanup_game_map(t_game *cub3d)
{
	if (cub3d->map.map)
		free_matrix(cub3d->map.map);
}

void	cleanup_game(t_game *cub3d)
{
	cleanup_game_textures(cub3d);
	cleanup_game_mlx(cub3d);
	cleanup_game_map(cub3d);
}
