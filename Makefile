# =================== #
#     VARIABLES       #
# =================== #

NAME    = cub3D
CC      = gcc
CFLAGS  = -Wall -Wextra -Werror -g
RM      = rm -rf

# =================== #
#     DIRECTORIES     #
# =================== #

LIBFT_DIR	= ./include/libft
LIBFT_FLAGS = -L$(LIBFT_DIR) -lft
MLX_DIR     = ./include/minilib_linux
MLX_FLAGS   = -L$(MLX_DIR) -lmlx -lXext -lX11
INC         = -Iinclude -I$(MLX_DIR) -I$(LIBFT_DIR)
OBJ_DIR     = obj

# ============ #
#   SOURCES    #
# ============ #

SRC = src/main.c \
	src/arg_validation.c \
	src/error.c \
	src/init_game.c \
	\
	src/parsing/main_parse.c \
	src/parsing/color/parse_color.c \
	src/parsing/color/color_storage.c \
	\
	src/parsing/map/map_flood_fill.c \
	src/parsing/map/map_storage.c \
	src/parsing/map/map_validation.c \
	\
	src/parsing/texture/parse_texture.c \
	src/parsing/texture/texture_storage.c \

OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

# ================= #
#     TARGETS       #
# ================= #

all: libft mlx $(NAME)

libft:
	@make -C $(LIBFT_DIR) > /dev/null 2>&1

mlx:
	@make -C $(MLX_DIR) > /dev/null 2>&1

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) $(MLX_FLAGS) $(LIBFT_FLAGS) -o $(NAME)
	@echo "✅ $(NAME) compiled"

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@

clean:
	@$(RM) $(OBJ_DIR)
	@make -C $(LIBFT_DIR) clean > /dev/null 2>&1
	@make -C $(MLX_DIR) clean > /dev/null 2>&1
	@echo "🧹 Object files removed"

fclean: clean
	@$(RM) $(NAME)
	@make -C $(LIBFT_DIR) fclean > /dev/null 2>&1
	@echo "🗑️  $(NAME) removed"

re: fclean all

.PHONY: all libft mlx clean fclean re