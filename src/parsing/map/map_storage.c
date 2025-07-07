/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_storage.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonimo <antonimo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 11:44:33 by antonimo          #+#    #+#             */
/*   Updated: 2025/07/07 12:55:54 by antonimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	validate_map_chr(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '1' && line[i] != '0'
			&& line[i] != 'N' && line[i] != 'S' && line[i] != 'E'
			&& line[i] != 'W')
			return (false);
		i++;
	}
	return (true);
}

static bool	store_map_line(char *line, t_game *cub3d)
{
	cub3d->map.map_started = true;
	if (!cub3d->map.map)
	{
		cub3d->map.map = create_matrix(0);
		if (!cub3d->map.map)
			return (false);
	}
	cub3d->map.map = matrix_append(cub3d->map.map, line);
	if (!cub3d->map.map)
		return (false);
	free(line);
	return (true);
}

bool	get_map_data(char *line, t_game *cub3d)
{
	char	*trimmed;

	trimmed = ft_strtrim(line, "\n");
	if (!trimmed)
		return (false);
	if (*trimmed == '\0')
	{
		free(trimmed);
		if (cub3d->map.map_started)
		{
			write_error("Empty line found within map");
			return (false);
		}
		return (true);
	}
	if (validate_map_chr(trimmed))
		return (store_map_line(trimmed, cub3d));
	free(trimmed);
	if (cub3d->map.map_started)
	{
		write_error("Invalid content after map started");
		return (false);
	}
	return (true);
}
