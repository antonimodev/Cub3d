/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonimo <antonimo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 11:41:04 by antonimo          #+#    #+#             */
/*   Updated: 2025/07/08 11:21:24 by antonimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	parsing(char **av, t_game *cub3d)
{
	int	fd;

	fd = open(av[1], O_RDONLY);
	if (!parse_line(&fd, cub3d))
	{
		cleanup_game(cub3d);
		close(fd);
		return (false);
	}
	close(fd);
	return (true);
}

bool	parse_line(int *fd, t_game *cub3d)
{
	char	*line;

	line = get_next_line(*fd);
	if (!line)
	{
		write_error("Failed to read the file.\n");
		return (false);
	}
	while (line)
	{
		if (!get_data_from_line(line, cub3d))
		{
			free(line);
			get_next_line(-1);
			return (false);
		}
		free(line);
		line = get_next_line(*fd);
	}
	if (!validate_assigned_params(cub3d))
		return (false);
	return (true);
}

bool	get_data_from_line(char *line, t_game *cub3d)
{
	if (!get_texture_path(line, cub3d))
		return (false);
	if (!get_color(line, cub3d))
		return (false);
	if (!get_map_data(line, cub3d))
		return (false);
	return (true);
}

bool	validate_assigned_params(t_game *cub3d)
{
	if (!cub3d->texture_paths.no || !cub3d->texture_paths.so
		|| !cub3d->texture_paths.ea || !cub3d->texture_paths.we)
	{
		write_error("Missing texture paths. "
			"All four textures (NO, SO, EA, WE) are required\n");
		return (false);
	}
	if (!cub3d->colors.floor_set || !cub3d->colors.ceiling_set)
	{
		write_error("Missing color definitions. "
			"Both Floor (F) and Ceiling (C) colors are required\n");
		return (false);
	}
	if (!validate_complete_map(cub3d))
		return (false);
	return (true);
}
