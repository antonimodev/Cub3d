#include "cub3d.h"

static bool	init_mlx(t_game *cub3d)
{
	cub3d->mlx = mlx_init();
	if (!cub3d->mlx)
	{
		write_error("Failed to initialize MiniLibX");
		return (false);
	}
	return (true);
}

static bool	init_window(t_game *cub3d)
{
	cub3d->window = mlx_new_window(cub3d->mlx, WIDTH, HEIGHT, "Cub3D");
	if (!cub3d->window)
	{
		write_error("Failed to create window");
		return (false);
	}
	return (true);
}

static bool	init_image(t_game *cub3d)
{
	cub3d->image = mlx_new_image(cub3d->mlx, WIDTH, HEIGHT);
	if (!cub3d->image)
	{
		write_error("Failed to create image");
		return (false);
	}
	return (true);
}

bool	init_game(t_game *cub3d)
{
	if (!init_mlx(cub3d))
		return (false);
	if (!init_window(cub3d))
	{
		cleanup_game(cub3d);
		return (false);
	}
	if (!init_image(cub3d))
	{
		cleanup_game(cub3d);
		return (false);
	}
	return (true);
}

// cleanup_game to free resources, probably it will change to another location
void	cleanup_game(t_game *cub3d)
{
	if (cub3d->image)
		mlx_destroy_image(cub3d->mlx, cub3d->image);
	if (cub3d->window)
		mlx_destroy_window(cub3d->mlx, cub3d->window);
	if (cub3d->mlx)
		mlx_destroy_display(cub3d->mlx);
}
