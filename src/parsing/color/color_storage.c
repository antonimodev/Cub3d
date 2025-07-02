#include "cub3d.h"

static bool validate_color_values(int red, int green, int blue)
{
	if (red < 0 || red > 255 || green < 0 || green > 255 || blue < 0 || blue > 255)
	{
		write_error("Error\nColor values must be between 0 and 255\n");
		return (false);
	}
	return (true);
}

static bool store_floor_color(int red, int green, int blue, t_game *cub3d)
{
	if (cub3d->colors.floor_set)
	{
		write_error("Error\nDuplicate Floor color definition\n");
		return (false);
	}
	cub3d->colors.floor.red = red;
	cub3d->colors.floor.green = green;
	cub3d->colors.floor.blue = blue;
	cub3d->colors.floor_set = true;
	return (true);
}

static bool store_ceiling_color(int red, int green, int blue, t_game *cub3d)
{
	if (cub3d->colors.ceiling_set)
	{
		write_error("Error\nDuplicate Ceiling color definition\n");
		return (false);
	}
	cub3d->colors.ceiling.red = red;
	cub3d->colors.ceiling.green = green;
	cub3d->colors.ceiling.blue = blue;
	cub3d->colors.ceiling_set = true;
	return (true);
}

bool	validate_and_store_color(char **color_values, t_color_type type, t_game *cub3d)
{
	int	red;
	int	green;
	int	blue;

	red = ft_atoi(color_values[0]);
	green = ft_atoi(color_values[1]);
	blue = ft_atoi(color_values[2]);
	if (!validate_color_values(red, green, blue))
		return (false);
	if (type == COLOR_FLOOR)
		return (store_floor_color(red, green, blue, cub3d));
	else if (type == COLOR_CEILING)
		return (store_ceiling_color(red, green, blue, cub3d));
	return (true);
}
