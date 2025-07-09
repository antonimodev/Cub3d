/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonimo <antonimo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 10:53:33 by antonimo          #+#    #+#             */
/*   Updated: 2025/07/09 14:19:18 by antonimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int ac, char **av)
{
	t_game	cub3d;

	ft_memset(&cub3d, 0, sizeof(t_game));
	if (!validate_args(ac, av))
		return (EXIT_FAILURE);
	if (!parsing(av, &cub3d))
		return (EXIT_FAILURE);
	if (!init_game(&cub3d))
	{
		write_error("Failed to initialize game.");
		return (EXIT_FAILURE);
	}
	mlx_put_image_to_window(cub3d.mlx, cub3d.window, cub3d.image, 0, 0);
	mlx_loop(cub3d.mlx);
	cleanup_game(&cub3d);
	return (EXIT_SUCCESS);
}
