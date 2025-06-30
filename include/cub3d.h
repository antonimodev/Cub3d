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

/**
 * Initializes the game by setting up the MiniLibX, creating a window, and an image.
 * If any step fails, it cleans up resources and returns false.
 * @param cub3d Pointer to the game structure
 * @return true if initialization is successful, false otherwise
 */
bool    init_game(t_game *cub3d); // Initialize game parameters
void    cleanup_game(t_game *cub3d); // Clean up resources

/* ---------- ERROR.C (1) ----------*/

/**
 * Writes an error message to the standard error output.
 * @param message The error message to write
 */
void    write_error(const char *message);

/* ---------- PARSING.C (?) ---------- */


/* ---------- ARG_VALIDATION.C (4) ---------- */

/**
 * Validates command line arguments for the Cub3D game.
 * Checks if the number of arguments is correct, if the file has a valid extension,
 * and if the file can be accessed.
 * @param ac Argument count
 * @param av Matrix of arguments
 * @return true if arguments are valid, false otherwise
 */
bool    validate_args(int ac, char **av); // Validate command line arguments

/**
 * Checks if the file exists and can be opened for reading.
 * @param filename Name of the file to validate
 * @return true if file can be accessed, false otherwise
 */
bool	validate_file_access(const char *filename); // Check if the file can be accessed

#endif