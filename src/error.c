#include "cub3d.h"

void	write_error(const char *message)
{
    int i = 0;
    
    write(2, "Error: ", 7);
    while (message[i])
    {
        write(2, &message[i], 1);
        i++;
    }
    write(2, "\n", 1);
}

void	print_mlx_error(const char *message)
{
    write_error(message);
}