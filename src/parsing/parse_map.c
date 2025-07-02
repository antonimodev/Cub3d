#include "cub3d.h"

bool	get_map_data(char *line, t_game *cub3d)
{
	char	*trimmed;
	bool	result;

	trimmed = ft_strtrim(line, "\n");
	if (!trimmed) // If strtrim fails
		return (false);
	if (*trimmed == '\0') // Handle Empty lines
	{
		if (cub3d->map.map_started) // Empty line when map has started
		{
			write_error("Error\nEmpty line found within map");
			result = false;
		}
		else // map has not started yet, so true and go to next line
			result = true;
		free(trimmed);
		return (result);
	}
	if (validate_map_chr(trimmed)) 	// Check if line contains valid map characters
		return (store_map_line(trimmed, cub3d));
	if (cub3d->map.map_started) // If map has started but line is invalid
	{
		write_error("Error\nInvalid content after map started");
		free(trimmed);
		return (false);
	}
	free(trimmed);
	return (true);
}

bool	validate_map_chr(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '1' && line[i] != '0' &&
			line[i] != 'N' && line[i] != 'S' && line[i] != 'E' &&
			line[i] != 'W')
			return (false);
		i++;
	}
	return (true);
}

bool	store_map_line(char *line, t_game *cub3d)
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
	return (true);
}