#include "cub3d.h"

static bool store_north_texture(const char *path, t_game *cub3d)
{
	if (cub3d->texture_paths.no)
	{
		write_error("Error\nDuplicate North texture definition\n");
		return (false);
	}
	cub3d->texture_paths.no = ft_strdup(path);
	return (true);
}

static bool store_south_texture(const char *path, t_game *cub3d)
{
	if (cub3d->texture_paths.so)
	{
		write_error("Error\nDuplicate South texture definition\n");
		return (false);
	}
	cub3d->texture_paths.so = ft_strdup(path);
	return (true);
}

static bool store_east_texture(const char *path, t_game *cub3d)
{
	if (cub3d->texture_paths.ea)
	{
		write_error("Error\nDuplicate East texture definition\n");
		return (false);
	}
	cub3d->texture_paths.ea = ft_strdup(path);
	return (true);
}

static bool store_west_texture(const char *path, t_game *cub3d)
{
	if (cub3d->texture_paths.we)
	{
		write_error("Error\nDuplicate West texture definition\n");
		return (false);
	}
	cub3d->texture_paths.we = ft_strdup(path);
	return (true);
}

bool	store_texture_path(const char *path, t_texture_type type, t_game *cub3d)
{
	if (type == TEXTURE_NORTH)
		return (store_north_texture(path, cub3d));
	else if (type == TEXTURE_SOUTH)
		return (store_south_texture(path, cub3d));
	else if (type == TEXTURE_EAST)
		return (store_east_texture(path, cub3d));
	else if (type == TEXTURE_WEST)
		return (store_west_texture(path, cub3d));
	return (false);
}