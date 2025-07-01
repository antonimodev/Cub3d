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

MLX_DIR     = ./include/minilibx-linux
MLX_FLAGS   = -L$(MLX_DIR) -lmlx -lXext -lX11
INC         = -Iinclude -I$(MLX_DIR)

# ============ #
#   SOURCES    #
# ============ #

SRC = src/main.c \
      src/arg_validation.c \
      src/error.c \
      src/init_game.c \
	  \
      src/parsing/main_parse.c \
      src/parsing/parse_color.c \
      src/parsing/parse_map.c \
      src/parsing/parse_texture.c \
	  src/parsing/texture_storage.c \
	  src/parsing/color_storage.c \

OBJ = $(SRC:.c=.o)

# ================= #
#     TARGETS       #
# ================= #

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) $(MLX_FLAGS) -o $(NAME)
	@echo "✅ $(NAME) compiled"

%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@

clean:
	@$(RM) $(OBJ)
	@echo "🧹 Object files removed"

fclean: clean
	@$(RM) $(NAME)
	@echo "🗑️  $(NAME) removed"

re: fclean all

.PHONY: all clean fclean re
