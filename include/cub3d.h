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


typedef struct s_game
{
    void    *mlx;
    void    *window;
    void    *image;
} t_game;

#endif