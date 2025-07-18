/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonimo <antonimo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 10:53:33 by antonimo          #+#    #+#             */
/*   Updated: 2025/07/18 12:32:17 by antonimo         ###   ########.fr       */
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
	cleanup_game(&cub3d);
	return (EXIT_SUCCESS);
}
