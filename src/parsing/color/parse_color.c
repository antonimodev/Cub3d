#include "cub3d.h"

bool	get_color(char *line, t_game *cub3d)
{
	if (ft_strnstr(line, "F ", 2))
		return (process_color_line(line, "F ", COLOR_FLOOR, cub3d));
	else if (ft_strnstr(line, "C ", 2))
		return (process_color_line(line, "C ", COLOR_CEILING, cub3d));
	return (true);
}

bool	process_color_line(char *line, const char *prefix, t_color_type type, t_game *cub3d)
{
	char	*clean_color;
	char	**color_values;

	clean_color = ft_strtrim(line + ft_strlen(prefix), " \n\t");
	if (!clean_color || ft_strlen(clean_color) == 0)
	{
		write_error("Error\nEmpty color value\n");
		free(clean_color);
		return (false);
	}
	color_values = ft_split(clean_color, ',');
	free(clean_color);
	if (!color_values || matrix_len(color_values) != 3)
	{
		write_error("Error\nInvalid color format. Expected R,G,B\n");
		free_matrix(color_values);
		return (false);
	}
	if (!validate_and_store_color(color_values, type, cub3d))
	{
		free_matrix(color_values);
		return (false);
	}
	free_matrix(color_values);
	return (true);
}
