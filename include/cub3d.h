/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonimo <antonimo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 10:45:38 by antonimo          #+#    #+#             */
/*   Updated: 2025/07/16 13:35:18 by antonimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

/* INCLUDES */
# include <math.h>		// For mathematical functions
# include <stddef.h>	// For NULL
# include <unistd.h>	// For read, write, close
# include <fcntl.h>		// For open
# include <stdio.h>		// For printf, perror
# include <stdlib.h>	// For malloc, free, exit
# include <string.h>	// For strerror
# include <sys/time.h>	// For gettimeofday
# include <stdbool.h>	// For bool, true, false
# include "mlx.h"		// For MiniLibX functions
# include "libft.h"		// For Libft functions

/* DIMENSIONS */
# define WIDTH	1920
# define HEIGHT	1080
# define BLOCK	64

/* MAP */
# define FLOOR	'0'
# define WALL	'1'

/* MATHS */
# define PI		3.1416	// PI with less decimals

/* MOVEMENTS */
# define KEY_W				119
# define KEY_A				97
# define KEY_S				115
# define KEY_D				100

/* ROTATIONS */
# define KEY_LEFT  			65361
# define KEY_RIGHT 			65363

/* QUIT */
# define KEY_ESC  			65307

/* EVENTS */
# define CLOSE_WINDOW		17
# define KEY_PRESSED		2
# define KEY_RELEASED		3

/* DEFAULT VALUES */
# define ANGLE_SPEED		0.08
# define PLAYER_SPEED		2

/* ENUMS */
typedef enum e_texture_type
{
	TEXTURE_NORTH,
	TEXTURE_SOUTH,
	TEXTURE_EAST,
	TEXTURE_WEST
}	t_tex_type;

typedef enum e_player_direction
{
	NORTH = 'N',
	SOUTH = 'S',
	EAST = 'E',
	WEST = 'W'
}	t_direction;

typedef enum e_color_type
{
	COLOR_FLOOR,
	COLOR_CEILING
}	t_color_type;

/* STRUCTURES */

typedef struct s_player_angle
{
	float	current_angle;
	float	angle_speed;
	float	cos_angle;		// May be deleted in future if only has 1 use
	float	sin_angle;		// May be deleted in future if only has 1 use
} t_angle;

typedef struct s_player_move
{
	bool	forward;
	bool	back;
	bool	left;
	bool	right;
}	t_move;

typedef struct s_player_rotate
{
	bool	left;
	bool	right;
}	t_rotate;

typedef struct s_coords
{
	float	x;
	float	y;
} t_coords;

typedef struct s_player_pos
{
	t_coords	coords;
	t_angle		angle;
	t_direction	dir;
	t_move		move;
	t_rotate	rotate;
}	t_player_pos;

typedef struct s_textures // Testing about store texture paths
{
	char	*no; // North texture path
	char	*so; // South texture path
	char	*ea; // East texture path
	char	*we; // West texture path
}	t_textures;

typedef struct s_colors // Testing about store colors
{
	int	red;
	int	green;
	int	blue;
}	t_colors;

typedef struct s_game_colors
{
	t_colors	floor; // Floor color
	t_colors	ceiling; // Ceiling color
	bool		floor_set; // Flag to track if floor color is set
	bool		ceiling_set; // Flag to track if ceiling color is set
}	t_game_colors;

typedef struct s_map
{
	char	**map;
	bool	map_started; // Flag to indicate if the map has started
}	t_map;

typedef struct s_game
{
	void			*mlx;
	void			*window;
	void			*image;
	t_textures		texture_paths;
	t_game_colors	colors;
	t_map			map;
	t_player_pos	player; // Player position in the map

	// TESTING
	int size_line;
	int	bpp;
	char *data;
	int endian;
}	t_game;

/* SRC */

/* ---------- ARG_VALIDATION.C (4) ---------- */

/**
 * Validates command line arguments for the Cub3D game.
 * Checks if the number of arguments is correct,
 * if the file has a valid extension,
 * and if the file can be accessed.
 * @param ac Argument count
 * @param av Matrix of arguments
 * @return true if arguments are valid, false otherwise
 */
bool	validate_args(int ac, char **av); // Validate command line arguments

/**
 * Checks if the file exists and can be opened for reading.
 * @param filename Name of the file to validate
 * @return true if file can be accessed, false otherwise
 */
bool	validate_file_access(const char *filename);

/* ---------- ERROR.C (1) ---------- */

/**
 * Writes an error message to the standard error output.
 * @param message The error message to write
 */
void	write_error(const char *message);

/* ---------- INIT_GAME.C (4) ---------- */

/**
 * Initializes the game by setting up the MiniLibX,
 * creating a window, and an image.
 * If any step fails, it cleans up resources and returns false.
 * @param cub3d Pointer to the game structure
 * @return true if initialization is successful, false otherwise
 */
bool	init_game(t_game *cub3d); // Initialize game parameters

/* ---------- CLEAN.C (4) --------- */

void	cleanup_game(t_game *cub3d); // Clean up resources

/* PARSING */

/* ---------- MAIN_PARSE.C (5) ---------- */

/**
 * Parses the .cub file and fills the game structure with
 * texture paths, colors, and map data.
 * @param av Command line arguments
 * @param cub3d Pointer to the game structure to fill
 * @return true if parsing is successful, false otherwise
 */
bool	parsing(char **av, t_game *cub3d);

/**
 * Processes each line of the .cub file and extracts relevant data.
 * @param fd Pointer to the file descriptor of the .cub file
 * @param cub3d Pointer to the game structure to fill
 * @return true if line processing is successful, false otherwise
 */
bool	parse_line(int *fd, t_game *cub3d);

/**
 * Processes each line of the .cub file and extracts relevant data.
 * @param line The line to process
 * @param cub3d Pointer to the game structure to fill
 * @return true if line processing is successful, false otherwise
 */
bool	get_data_from_line(char *line, t_game *cub3d);

/**
 * Validates that all required parsing elements are complete and properly set.
 * @param cub3d Pointer to the game structure to validate
 * @return true if all required elements are present, false otherwise
 */
bool	validate_assigned_params(t_game *cub3d);

/* COLOR */

/* ---------- PARSE_COLOR.C (2) ---------- */

/**
 * Processes color lines (F, C).
 * @param line The line containing color information
 * @param cub3d Pointer to the game structure to fill
 * @return true if color processing is successful, false otherwise
 */
bool	get_color(char *line, t_game *cub3d);

/**
 * Processes color lines (F, C).
 * @param line The line containing color information
 * @param prefix The prefix to identify the color type (F or C)
 * @param type The type of color (FLOOR or CEILING)
 * @param cub3d Pointer to the game structure to fill
 * @return true if color processing is successful, false otherwise
 */
bool	process_color_line(char *line, const char *prefix, t_color_type type,
			t_game *cub3d);

/* ---------- COLOR_STORAGE.C (4) ---------- */

/**
 * Validates and stores the color values in the game structure.
 * @param color_values Array of color values (R, G, B)
 * @param type The type of color (FLOOR or CEILING)
 * @param cub3d Pointer to the game structure to fill
 * @return true if color values are valid and stored successfully
 */
bool	validate_and_store_color(char **color_values, t_color_type type,
			t_game *cub3d);

/* MAP */

/* ---------- MAP_FLOOD_FILL.C (1) ---------- */

/**
 * Validates if the map is properly enclosed using flood fill algorithm.
 * It checks if all spaces are reachable from the player's position and
 * if the map is surrounded by walls.
 * @param x The x-coordinate of the starting position
 * @param y The y-coordinate of the starting position
 * @param map The map to validate
 * @return true if the map is properly enclosed, false otherwise
 */
bool	validate_flood_fill(int x, int y, char **map);

/* ---------- MAP_STORAGE.C (3) ---------- */

/**
 * Processes map lines and stores them in the game structure.
 * It checks if the map has started, validates characters,
 * and appends lines to the map.
 * @param line The line to process
 * @param cub3d Pointer to the game structure to fill
 * @return true if map processing is successful, false otherwise
 */
bool	get_map_data(char *line, t_game *cub3d);

/* ---------- MAP_VALIDATION.C (5) ---------- */

/**
 * Validates that the map is complete and properly enclosed
 * using flood fill algorithm.
 * @param cub3d Pointer to the game structure to validate
 * @return true if the map is valid, false otherwise
 */
bool	validate_map_enclosed(t_game *cub3d);

/**
 * Validates that the map contains exactly one player character (N, S, E, W).
 * It checks if the player character is found and if there are no duplicates.
 * @param cub3d Pointer to the game structure to validate
 * @return true if the player is found and valid, false otherwise
 */
bool	find_and_validate_player(t_game *cub3d);

/**
 * Validates that the map is complete and properly enclosed.
 * Checks if the map has a player, if it is enclosed by walls,
 * and if it contains valid characters.
 * @param cub3d Pointer to the game structure to validate
 * @return true if the map is valid, false otherwise
 */
bool	validate_complete_map(t_game *cub3d);

/* TEXTURE */

/* ---------- PARSE_TEXTURE.C (2) ---------- */

/**
 * Processes texture path lines (NO, SO, EA, WE).
 * @param line The line containing texture information
 * @param cub3d Pointer to the game structure to fill
 * @return true if texture processing is successful, false otherwise
 */
bool	get_texture_path(char *line, t_game *cub3d);

/**
 * Processes texture path lines (NO, SO, EA, WE).
 * @param line The line containing texture information
 * @param prefix The prefix to identify the texture type (NO, SO, EA, WE)
 * @param type The type of texture (NORTH, SOUTH, EAST, WEST)
 * @param cub3d Pointer to the game structure to fill
 * @return true if texture processing is successful, false otherwise
 */
bool	process_texture_line(char *line, const char *prefix, t_tex_type type,
			t_game *cub3d);

/* ---------- TEXTURE_STORAGE.C (5) ---------- */

/**
 * Stores the texture path in the game structure based on the texture type.
 * @param path The path to the texture
 * @param type The type of texture (NORTH, SOUTH, EAST, WEST)
 * @param cub3d Pointer to the game structure to fill
 * @return true if stored successfully, false if duplicate found
 */
bool	store_texture_path(const char *path, t_tex_type type, t_game *cub3d);

/* HOOKS */

/* ---------- HOOK.C (2) ---------- */

/**
 * Handle key press event.
 * @param param Pointer to the game structure
 * @return ???
 */
int		handle_key_press(int key, void *param);

/**
 * Handle key release event.
 * @param param Pointer to the game structure
 * @return ???
 */
int		handle_key_release(int key, void *param);

/**
 * Handle close button event to close the window.
 * @param param Pointer to the game structure
 * @return
 */
int		handle_close_window(void *param);

/* PLAYER_MOVE */

/* ---------- ADVANCED_MOVES.C (5) ---------- */

/**
 * Main function that contains diagonal movements logic.
 * @param player Player structure.
 */
void	advanced_move(t_player_pos *player);

/* ---------- MOVEMENT.C (1) ---------- */

/**
 * Main function that contains all movement logic
 * @param player Player structure.
 */
void	move_player(t_player_pos *player);

/* ---------- BASIC_MOVES.C (5) ---------- */

/**
 * Main function that contains basic movements logic
 * @param player Player structure.
 */
void	basic_move(t_player_pos *player);

/**
 * Move player forward
 * @param player Player structure.
 */
void	move_forward(t_player_pos *player);

/**
 * Move player left
 * @param player Player structure.
 */
void	move_left(t_player_pos *player);

/**
 * Move player back
 * @param player Player structure.
 */
void	move_back(t_player_pos *player);

/**
 * Move player right
 * @param player Player structure.
 */
void	move_right(t_player_pos *player);


/* ---------- ANGLES.C (4) ---------- */

/**
 * Initialize player angle based on his orientation (N,S,E,W)
 * @param cub3d Game structure.
 */
void	init_angles(t_player_pos *player);

/**
 * Normalize angles if they're greater than 360º or
 * less than 0º
 * @param cub3d Game structure.
 */
void	normalize_angle(t_player_pos *player);

/* ---------- ROTATE.C (4) ---------- */

/**
 * Main function that contains rotating player logic
 * @param cub3d Game structure.
 */
void	rotate_player(t_player_pos *player);

/**
 * Rotate player to left direction
 * @param cub3d Game structure.
 */
void	rotate_left(t_player_pos *player);

/**
 * Rotate player to right direction
 * @param cub3d Game structure.
 */
void	rotate_right(t_player_pos *player);

/* TO SET SOMEWHERE */
void	render_frame(t_game *cub3d);
void	put_pixel(int x, int y, int color, t_game *cub3d);


/* RAYCASTING */

/* ---------- RAYCASTING.C (3) ---------- */

/**
 * WRITE HERE
 */
void	raycast(t_game *cub3d);

/* RENDER */

/* ---------- RENDER_BACKGROUND.C (2) ---------- */

/**
 * WRITE HERE
 */
void	draw_background(t_game *cub3d);


/* PROBABLY IN THE FUTURE WE'LL CHANGE THE POSITION OF THESE FUCTIONS */
void	draw_square(t_game *cub3d, int size, int x, int y); // TESTING, DON'T USE FOR :D
void	draw_walls(t_game *cub3d);


#endif