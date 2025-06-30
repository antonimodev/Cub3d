#include "cub3d.h"

int main(void)
{
	t_game  cub3d;

	if (!init_game(&cub3d))
	{
		write_error("Failed to initialize game");
		return (EXIT_FAILURE);
	}

	mlx_loop(cub3d.mlx);
	cleanup_game(&cub3d);
	return (EXIT_SUCCESS);
}