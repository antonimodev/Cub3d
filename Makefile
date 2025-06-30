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
MLX_LIB     = $(MLX_DIR)/libmlx.a
MLX_FLAGS   = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm
INC         = -Iinclude -I$(MLX_DIR)

# ============ #
#   SOURCES    #
# ============ #

SRC = src/main.c \
      src/init_game.c \
      src/error.c \

OBJ_DIR = Cub3d_OBJ
OBJ = $(SRC:src/%.c=$(OBJ_DIR)/%.o)

# ================= #
#     TARGETS       #
# ================= #

all: $(MLX_LIB) $(NAME)

$(MLX_LIB):
	@echo "🔨 Compiling MiniLibX..."
	@$(MAKE) -C $(MLX_DIR) > /dev/null 2>&1
	@echo "✅ MiniLibX compiled"

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) $(MLX_FLAGS) -o $(NAME)
	@echo "✅ $(NAME) compiled"

%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(OBJ_DIR)/%.o: src/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@

clean:
	@$(RM) $(OBJ_DIR)
	@$(MAKE) -C $(MLX_DIR) clean > /dev/null 2>&1
	@echo "🧹 Object files removed"
	@echo "🧹 MiniLibX cleaned"

fclean: clean
	@$(RM) $(NAME)
	@echo "🗑️  $(NAME) removed"

re: fclean all

.PHONY: all clean fclean re
