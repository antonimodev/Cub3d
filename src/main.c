#include "cub3d.h"

void    init_game(t_game *cub3d)
{
    cub3d->mlx = mlx_init(); // Should be protected?
    cub3d->window = mlx_new_window(cub3d->mlx, 1280, 720, "Cub3D TEST");
    cub3d->image = mlx_new_image(cub3d->mlx, 1280, 720);
}

int main(void)
{
    t_game  cub3d;

    init_game(&cub3d);
    mlx_loop(cub3d.mlx);
    return 0;
}