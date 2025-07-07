/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonimo <antonimo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 11:42:12 by antonimo          #+#    #+#             */
/*   Updated: 2025/07/07 13:48:55 by antonimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	get_texture_path(char *line, t_game *cub3d)
{
	if (ft_strnstr(line, "NO ", 3))
		return (process_texture_line(line, "NO ", TEXTURE_NORTH, cub3d));
	else if (ft_strnstr(line, "SO ", 3))
		return (process_texture_line(line, "SO ", TEXTURE_SOUTH, cub3d));
	else if (ft_strnstr(line, "EA ", 3))
		return (process_texture_line(line, "EA ", TEXTURE_EAST, cub3d));
	else if (ft_strnstr(line, "WE ", 3))
		return (process_texture_line(line, "WE ", TEXTURE_WEST, cub3d));
	return (true);
}

bool	process_texture_line(char *line, const char *prefix, t_tex_type type,
	t_game *cub3d)
{
	char	*clean_path;

	clean_path = ft_strtrim(line + ft_strlen(prefix), " \n\t");
	if (!clean_path || ft_strlen(clean_path) == 0)
	{
		write_error("Empty texture path\n");
		free(clean_path);
		return (false);
	}
	if (!validate_file_access(clean_path))
	{
		write_error("Invalid texture path\n");
		free(clean_path);
		return (false);
	}
	if (!store_texture_path(clean_path, type, cub3d))
	{
		free(clean_path);
		return (false);
	}
	free(clean_path);
	return (true);
}
