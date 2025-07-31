/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonimo <antonimo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 11:00:50 by antonimo          #+#    #+#             */
/*   Updated: 2025/07/31 14:23:46 by antonimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	cleanup_game_textures(t_game *cub3d)
{
    if (cub3d->wall_no.ptr)
        mlx_destroy_image(cub3d->mlx, cub3d->wall_no.ptr);
    if (cub3d->texture_paths.no)
        free(cub3d->texture_paths.no);

    if (cub3d->wall_so.ptr)
        mlx_destroy_image(cub3d->mlx, cub3d->wall_so.ptr);
    if (cub3d->texture_paths.so)
        free(cub3d->texture_paths.so);

    if (cub3d->wall_ea.ptr)
        mlx_destroy_image(cub3d->mlx, cub3d->wall_ea.ptr);
    if (cub3d->texture_paths.ea)
        free(cub3d->texture_paths.ea);

    if (cub3d->wall_we.ptr)
        mlx_destroy_image(cub3d->mlx, cub3d->wall_we.ptr);
    if (cub3d->texture_paths.we)
        free(cub3d->texture_paths.we);
}

static void	cleanup_game_mlx(t_game *cub3d)
{
	if (cub3d->image.ptr)
		mlx_destroy_image(cub3d->mlx, cub3d->image.ptr);
	if (cub3d->window)
		mlx_destroy_window(cub3d->mlx, cub3d->window);
	if (cub3d->mlx)
	{
		mlx_destroy_display(cub3d->mlx);
		free(cub3d->mlx);
	}
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
