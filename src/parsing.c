#include "cub3d.h"

// Get each line of .cub file
// Check if each line is valid
// Store the data in the game structure
// Return true if parsing is successful, false otherwise

bool    parsing(char **av)
{
    int     fd;
    char    **matrix;

    fd = open(av[1], O_RDONLY);
    parse_line(&fd);
}

void    parse_line(int *fd)
{
    char    *line;

    line = get_next_line(*fd);
    if (!line)
    {
        write_error("Error\nFailed to read the file.\n");
        return;
    }
    while (line)
    {
        get_data_from_line(line); // Check line to store data in the game structure
        free(line);
        line = get_next_line(*fd);
    }
}


// Data to be checked:

/* get_texture_path() */
// - NO path ✅
// - SO path ✅
// - WE path ✅
// - EA path ✅

/* get_color() */
// - F color
// - C color

/* get_map_data() */
// - Map data

bool    get_data_from_line(char *line)
{
    if (!get_texture_path(line)) // North, South, West, East texture paths
		return (false); // If texture path is invalid, return false
    if (!get_color(line)) // Ceiling + Floor colors
		return (false); // If color is invalid, return false
    if (!get_map_data(line)) // Map data
		return (false); // If map data is invalid, return false
	return (true);
}

bool    get_texture_path(char *line)
{
	if (ft_strnstr(line, "NO ", 3))
		return (process_texture_line(line, "NO ", "North"));
	else if (ft_strnstr(line, "SO ", 3))
		return (process_texture_line(line, "SO ", "South"));
	else if (ft_strnstr(line, "EA ", 3))
		return (process_texture_line(line, "EA ", "East"));
	else if (ft_strnstr(line, "WE ", 3))
		return (process_texture_line(line, "WE ", "West"));
	return (true);
}

bool    process_texture_line(char *line, const char *prefix, const char *direction)
{
	char	*clean_path;

	clean_path = ft_strtrim(line + ft_strlen(prefix), " \n\t");
	if (!clean_path || ft_strlen(clean_path) == 0)
	{
		write_error("Error\nEmpty texture path\n");
		free(clean_path);
		return (false);
	}
	if (!validate_file_access(clean_path))
	{
		write_error("Error\nInvalid texture path\n");
		free(clean_path);
		return (false);
	}
	// FUNCTION to store the texture path in the game structure?
	//store_texture_path(clean_path, direction);
	free(clean_path);
	return (true);
}

void	store_texture_path(const char *path, const char *direction)
{
	if (direction == "North") // Store North texture path
		// cub3d.texture_paths.no = ft_strdup(path);
	else if (direction == "South") // Store South texture path
		// cub3d.texture_paths.so = ft_strdup(path);
	else if (direction == "East") // Store East texture path
		// cub3d.texture_paths.ea = ft_strdup(path);
	else if (direction == "West") // Store West texture path
		// cub3d.texture_paths.we = ft_strdup(path);
}

bool	get_color(char *line)
{
	// Search for "F " or "C "
	// If found, split it by ',' and check if there are 3 numbers
	// if valid, ft_atoi each value and store in the game structure
	if (ft_strnstr(line, "F ", 2))
		return (process_color_line(line, "F ", "Floor"));
	else if (ft_strnstr(line, "C ", 2))
		return (process_color_line(line, "C ", "Ceiling"));
	return (true);
}

bool	process_color_line(char *line, const char *prefix, const char *color_type)
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
		write_error("Error\nInvalid color format\n");
		free_matrix(color_values);
		return (false);
	}
	// Atoi each value and check if they're valid (0-255)
}

bool	validate_color_values(char **color_values)
{
	int	red;
	int	green;
	int	blue;

	red = ft_atoi(color_values[0]);
	green = ft_atoi(color_values[1]);
	blue = ft_atoi(color_values[2]);
	if (red < 0 || red > 255 || green < 0 || green > 255 || blue < 0 || blue > 255)
	{
		write_error("Error\nColor values must be between 0 and 255\n");
		return (false);
	}
	return (true);
}