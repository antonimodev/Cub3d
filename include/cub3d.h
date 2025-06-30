#ifndef CUB3D_H
#define CUB3D_H

/* INCLUDES */
#include <math.h>       // For mathematical functions
#include <stddef.h>     // For NULL
#include <unistd.h>     // For read, write, close
#include <fcntl.h>      // For open
#include <stdio.h>      // For printf, perror
#include <stdlib.h>     // For malloc, free, exit
#include <string.h>     // For strerror
#include <sys/time.h>   // For gettimeofday
#include <stdbool.h>    // For bool, true, false
#include "mlx.h"        // For MiniLibX functions

/* DEFINES */
#define WIDTH 1280
#define HEIGHT 720

typedef struct s_game
{
    void    *mlx;
    void    *window;
    void    *image;
} t_game;

/* SRC */

/* ---------- INIT_GAME.C (5) ----------*/
bool    init_game(t_game *cub3d); // Initialize game parameters
void    cleanup_game(t_game *cub3d); // Clean up resources

/* ---------- ERROR.C (2) ----------*/
void    write_error(const char *message);
void    print_mlx_error(const char *context);

#endif