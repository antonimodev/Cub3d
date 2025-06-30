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
MLX_FLAGS   = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm
INC         = -Iinc -I$(MLX_DIR) # Revision

# ============ #
#   SOURCES    #
# ============ #

SRC = src/main.c \

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
