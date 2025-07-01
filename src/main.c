#include "cub3d.h"

int main(int ac, char **av)
{
	t_game  cub3d;
	
	ft_memset(&cub3d, 0, sizeof(t_game)); // Initializing game structure
	if (!validate_args(ac, av))
		return (EXIT_FAILURE);
	if (!parsing(av)) // Use &cub3d as parameter to store textures and other data?
		return (EXIT_FAILURE);
	if (!init_game(&cub3d))
	{
		write_error("Failed to initialize game");
		return (EXIT_FAILURE);
	}
	mlx_loop(cub3d.mlx);
	cleanup_game(&cub3d);
	return (EXIT_SUCCESS);
}